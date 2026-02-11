Ns_DbSpGetParams(Ns_DbHandle *handle)
{
    DbDriver *driverPtr = NsDbGetDriver(handle);
    Ns_Set   *aset = NULL;

    Ns_SetTrunc(handle->row, 0);
    if (handle->connected &&
	driverPtr != NULL &&
	driverPtr->spgetparamsProc != NULL) {

	aset = (*driverPtr->spgetparamsProc)(handle);
    }

    return aset;
}
