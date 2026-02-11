atoi_2(const unsigned char *s)
{
uint64_t res = 0;
unsigned char ch;

ch = *s - '0';
while(*s && (ch > 9))
        {
        s++;
	ch = *s - '0';
        }

while(ch < 10)
        {
        s++;
        res *= 10;
        res += ch;
	ch = *s - '0';
        }

return(res);
}
