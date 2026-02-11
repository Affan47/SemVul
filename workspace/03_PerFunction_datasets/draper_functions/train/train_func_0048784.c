vcdid_hash(char *s, int len)
{
unsigned int val=0;
int i;

s += len;

for(i=0;i<len;i++)
        {
	val *= 94;
        val += ((unsigned char)*(--s)) - 32;
        }

return(val);
}
