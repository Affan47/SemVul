c_ncaren (
    int ncid,
    int varid,
    const char* attname,
    const char* newname,
    int* rcode
)
{
    *rcode = ncattrename(ncid, varid, attname, newname) == -1
		? ncerr
		: 0;
}
