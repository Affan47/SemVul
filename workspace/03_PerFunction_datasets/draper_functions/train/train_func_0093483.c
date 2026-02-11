reserveDataBuffer(const size_t len, vector<unsigned char> &data)
{
#ifdef TEXTUREOBJ_USE_MEMPOOL
	TMyMemPool *pool = TMyMemPool::getInstance();
	if (pool)
	{
		CTexturedObject_MemPoolParams mem_params;
		mem_params.len = len;

		CTexturedObject_MemPoolData *mem_block = pool->request_memory(mem_params);
		if (mem_block)
		{

			data.swap(mem_block->data);
			delete mem_block;
		}
	}
#endif
	data.resize(len);
	return ((unsigned char*)(((POINTER_TYPE)&data[0]) & (~((POINTER_TYPE)0x0F)) )) + 0x10;
}
