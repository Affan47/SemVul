put_zone(byte *vals,int n,const char *tag)
{
    add_tag(tag);
    for(int i=0;i<(n+7)/8;i++){put_uint(vals[i],TMin(8,n-8*i),NULL);}
}
