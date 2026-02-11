c_nctlen (
    nc_type datatype,
    int* rcode
)
{
    int itype;

    *rcode = ((itype = (int) nctypelen (datatype)) == -1)
		?  ncerr
		: 0;

    return itype;
}
