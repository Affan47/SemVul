x_to_ASCII FCN((p0))
CONST outer_char HUGE*p0 C1("Character string to translate.")
{
static size_t bufsiz= 0;
static ASCII HUGE*buffer= NULL;

if(translate_ASCII)
{
ASCII HUGE*p;
CONST outer_char HUGE*q;

while(bufsiz<=STRLEN(p0)+1)
{
if(buffer==NULL)
buffer= GET_MEM("x_to_ASCII_buf",bufsiz= 32,ASCII);

else
{
buffer= (ASCII HUGE*)REALLOC(buffer,bufsiz+32,bufsiz);
bufsiz+= 32;
}

if(buffer==NULL)

fatal(ERR_C,OC("!! No more memory (x_to_ASCII)"),OC(""));
}

for(p= buffer,q= p0;*q;p++,q++)
*p= XORD(*q);
*p= '\0';

return buffer;
}
else
return(ASCII HUGE*)p0;
}
