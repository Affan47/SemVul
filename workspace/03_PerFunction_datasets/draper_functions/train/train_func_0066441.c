compare_text FCN((t0,t1))
text_pointer t0 C0("")
text_pointer t1 C1("")
{
token_pointer p0,p0_end,p1;

if(t0==NULL||t1==NULL)return NO;

t0= indirect(t0);t1= indirect(t1);

p0= *t0;p0_end= *(t0+1);
p1= *t1;

while(p0<p0_end)
{
if(*p0==072)return YES;
if(*p0++!=*p1++)return NO;
}

return YES;
}
