fstWriterVarint(FILE *handle, uint64_t v)
{
uint64_t nxt;
unsigned char buf[10];
unsigned char *pnt = buf;
int len;

while((nxt = v>>7))
        {
        *(pnt++) = (v&0x7f) | 0x80;
        v = nxt;
        }
*(pnt++) = (v&0x7f);

len = pnt-buf;
fstFwrite(buf, len, 1, handle);
return(len);
}
