evcd_strcpy(char *dst, char *src, int dir)
{
static const char *evcd="DUNZduLHXTlh01?FAaBbCcf";
static const char *vcdi="01xz01zzzzzz01xz0011xxz";
static const char *vcdo="zzzzzz01xz0101xz1x0x01z";
const char  *vcd = dir ? vcdo : vcdi;
char ch;
int i;

while((ch=*src))
        {
        for(i=0;i<23;i++)
                {
                if(evcd[i]==ch)
                        {
                        *dst=vcd[i];
                        break;
                        }
                }
        if(i==23) *dst='x';

        src++;
        dst++;
        }

*dst=0;
}
