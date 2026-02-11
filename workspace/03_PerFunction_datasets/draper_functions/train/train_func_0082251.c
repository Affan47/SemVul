peek(UINT8* pbuff,UINT32* psize)
	{
		if(m_Queue==NULL||pbuff==NULL||psize==NULL)
			return E_UNKNOWN;
		if(*psize==0)
			return E_SUCCESS;
		m_pcsQueue->lock();
		UINT32 space=*psize;
		*psize=0;
		QUEUE* tmpQueue=m_Queue;
		while(space>=tmpQueue->size)
			{
				memcpy(pbuff,tmpQueue->pBuff+tmpQueue->index,tmpQueue->size);
				*psize+=tmpQueue->size;
				pbuff+=tmpQueue->size;
				space-=tmpQueue->size;
				tmpQueue=tmpQueue->next;
				if(tmpQueue==NULL)
					{
						m_pcsQueue->unlock();
						return E_SUCCESS;
					}
			}
		memcpy(pbuff,tmpQueue->pBuff+tmpQueue->index,space);
		*psize+=space;
		m_pcsQueue->unlock();
		return E_SUCCESS;
	}
