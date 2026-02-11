Create(size_t nbOfElements,double Probability)
{
	size_t nbOfBits;
	size_t k;
	BloomFilter *result;

	if (Probability >= 1.0 || Probability <= 0.0) {
		iError.RaiseError("BloomFilter.Create",CONTAINER_ERROR_BADARG);
		return NULL;
	}
	nbOfBits = -round(nbOfElements*log(Probability)/TWICE_LOG_2);
	k = round(0.7*nbOfBits/nbOfElements);
	result = CurrentAllocator->malloc(sizeof(BloomFilter) + k*sizeof(int));
	if (result == NULL) {
		goto errMem;
	}
	memset(result,0,sizeof(*result));
	result->bits = CurrentAllocator->malloc(1+nbOfBits/8);
	if (result->bits == NULL) {
		CurrentAllocator->free(result);
errMem:
		iError.RaiseError("BloomFilter.Create",CONTAINER_ERROR_NOMEMORY);
		return NULL;
	}
	memset(result->bits,0,1+nbOfBits/8);
	result->nbOfBits = nbOfBits;
	result->MaxNbOfElements = nbOfElements;
	result->HashFunctions = k;
	while (k > 0) {
		k--;
		result->Seeds[k] = rand();

	}
	result->Allocator = CurrentAllocator;
	return result;
}
