vcdid_hash(char *s, int len)
{
unsigned int val=0;
int i;

s+=(len-1);

for(i=0;i<len;i++)
        {
        val *= 94;
        val += (((unsigned char)*s) - 32);
        s--;
        }

return(val);
}
