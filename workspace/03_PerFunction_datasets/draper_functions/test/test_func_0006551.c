zero_ccodes(VOID)
{
int c;


for(c= 0;c<=127;c++)
{
ccode[c]= USED_BY_NEITHER;
cname[c]= OC("?");
}


{
ccode[0100]= 0100;


ccode[0173]= 0173;

ccode[0175]= 0175;

ccode[076]= ignore;


}


}
