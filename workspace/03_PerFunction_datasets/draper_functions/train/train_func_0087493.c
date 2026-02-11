CBFinalize(CircularBuffer *cb)
{
	if (cb == NULL) {
		iError.RaiseError("iCircularBuffer.Finalize",CONTAINER_ERROR_BADARG);
		return CONTAINER_ERROR_BADARG;
	}
	CBClear(cb);
	cb->Allocator->free(cb->data);
	cb->Allocator->free(cb);
	return 1;
}
