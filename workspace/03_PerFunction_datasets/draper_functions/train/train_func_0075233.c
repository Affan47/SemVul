wilc_mq_send(WILC_MsgQueueHandle *pHandle,
			     const void *pvSendBuffer, u32 u32SendBufferSize)
{
	unsigned long flags;
	Message *pstrMessage = NULL;

	if ((!pHandle) || (u32SendBufferSize == 0) || (!pvSendBuffer)) {
		PRINT_ER("pHandle or pvSendBuffer is null\n");
		return -EFAULT;
	}

	if (pHandle->bExiting) {
		PRINT_ER("pHandle fail\n");
		return -EFAULT;
	}


	pstrMessage = kmalloc(sizeof(Message), GFP_ATOMIC);
	if (!pstrMessage)
		return -ENOMEM;

	pstrMessage->u32Length = u32SendBufferSize;
	pstrMessage->pstrNext = NULL;
	pstrMessage->pvBuffer = kmemdup(pvSendBuffer, u32SendBufferSize,
					GFP_ATOMIC);
	if (!pstrMessage->pvBuffer) {
		kfree(pstrMessage);
		return -ENOMEM;
	}

	spin_lock_irqsave(&pHandle->strCriticalSection, flags);


	if (!pHandle->pstrMessageList) {
		pHandle->pstrMessageList  = pstrMessage;
	} else {
		Message *pstrTailMsg = pHandle->pstrMessageList;

		while (pstrTailMsg->pstrNext)
			pstrTailMsg = pstrTailMsg->pstrNext;

		pstrTailMsg->pstrNext = pstrMessage;
	}

	spin_unlock_irqrestore(&pHandle->strCriticalSection, flags);

	up(&pHandle->hSem);

	return 0;
}
