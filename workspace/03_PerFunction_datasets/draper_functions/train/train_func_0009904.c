__log_persistswap(persist)
	LOGP *persist;
{
	M_32_SWAP(persist->magic);
	M_32_SWAP(persist->version);
	M_32_SWAP(persist->log_size);
	M_32_SWAP(persist->notused);
}
