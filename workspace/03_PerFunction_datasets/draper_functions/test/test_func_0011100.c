vzt_wr_emit_uv64z(struct vzt_wr_trace *lt, vztint64_t v)
{
int nmemb;
vztint64_t nxt;
unsigned int oldpnt = lt->gzbufpnt;

while((nxt = v>>7))
        {
        lt->gzdest[lt->gzbufpnt++] = (v&0x7f);
        v = nxt;
        }
lt->gzdest[lt->gzbufpnt++] = (v&0x7f) | 0x80;

lt->zpackcount+=(lt->gzbufpnt - oldpnt);
lt->position+=(lt->gzbufpnt - oldpnt);
nmemb=gzwrite_buffered(lt);

return(nmemb);
}
