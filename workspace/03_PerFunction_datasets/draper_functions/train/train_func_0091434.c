__ecereNameSpace__ecere__sys__UTF8toISO8859_1(char * source, char * dest, int max)
{
unsigned int ch;
int nb;
int c;
int d = 0;

for(c = 0; (ch = __ecereNameSpace__ecere__sys__UTF8GetChar(source + c, &nb)) && d < max - 1; c += nb)
{
if(ch < 256)
dest[d] = (unsigned char)ch;
else
dest[d] = '?';
d++;
}
dest[d] = (char)0;
return d;
}
