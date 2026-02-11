CreateCBWithAllocator(size_t sizElement,size_t sizeBuffer,const ContainerAllocator *allocator)
{
	CircularBuffer *result;

	if (sizElement == 0 || sizeBuffer == 0 || allocator == NULL) {
		iError.RaiseError("iCircularBuffer.Create",CONTAINER_ERROR_BADARG);
		return NULL;
	}
	result = allocator->malloc(sizeof(CircularBuffer));
	if (result == NULL) {
		iError.RaiseError("iCircularBuffer.Create",CONTAINER_ERROR_NOMEMORY);
		return NULL;
	}
	memset(result,0,sizeof(CircularBuffer));
	result->maxCount = sizeBuffer;
	result->ElementSize = sizElement;
	result->Allocator = (ContainerAllocator *)allocator;
	sizElement = sizElement*sizeBuffer;
	result->data = allocator->malloc(sizElement);
	if (result->data == NULL) {
		allocator->free(result);
		iError.RaiseError("iCircularBuffer.Create",CONTAINER_ERROR_NOMEMORY);
		return NULL;
	}
	return result;
}
