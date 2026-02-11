wilc_mq_create(WILC_MsgQueueHandle *pHandle)
{
	spin_lock_init(&pHandle->strCriticalSection);
	sema_init(&pHandle->hSem, 0);
	pHandle->pstrMessageList = NULL;
	pHandle->u32ReceiversCount = 0;
	pHandle->bExiting = false;
	return 0;
}
