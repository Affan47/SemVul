ocdumpmemdata(OCmemdata* memdata, OCbytes* buf)
{
    if(memdata == NULL || buf == NULL) return;
    ocdumpmemdata1(memdata,buf,0);
}
