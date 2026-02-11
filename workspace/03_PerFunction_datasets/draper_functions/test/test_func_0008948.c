commas FCN((l))
unsigned long l C1("")
{
outer_char temp[50],*p;
outer_char temp1[100],*p1;
int n0,n;
int len;

p= temp;
p1= temp1;

#if 0
if(l<0)
{
*p1++= '-';
l= -l;
}
#endif

sprintf((char*)temp,"%lu",l);

len= STRLEN(temp);

n= 3-len%3;

while(*p)
{
*p1++= *p++;
n++;
if(n%3==0)
*p1++= ',';
}

p1[-1]= '\0';

return push_buf(&c_buf,temp1);
}
