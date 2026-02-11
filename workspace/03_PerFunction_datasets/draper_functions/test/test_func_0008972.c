remove(UINT32* psize)
	{
		if(m_Queue==NULL||psize==NULL)
			return E_UNKNOWN;
		if(*psize==0)
			return E_SUCCESS;
		m_pcsQueue->lock();
		UINT32 space=*psize;
		*psize=0;
		while(space>=m_Queue->size)
			{
				*psize+=m_Queue->size;
				space-=m_Queue->size;
				m_nQueueSize-=m_Queue->size;
				QUEUE* tmp=m_Queue;
				m_Queue=m_Queue->next;


				delete[] tmp->pBuff;
				tmp->pBuff = NULL;
				delete tmp;
				tmp = NULL;
				if(m_Queue==NULL)
					{
						m_pcsQueue->unlock();
						return E_SUCCESS;
					}
			}
		if(space>0)
			{
				*psize+=space;
				m_Queue->size-=space;
				m_nQueueSize-=space;
				m_Queue->index+=space;

			}
		m_pcsQueue->unlock();
		return E_SUCCESS;
	}
