CoPostQueueMail(OS_EventID id,void* pmail) {
	P_ECB pecb;
	P_QCB pqcb;
#if CFG_PAR_CHECKOUT_EN >0
	if(id >= CFG_MAX_EVENT) {
		return E_INVALID_ID;
	}
#endif

	pecb = &EventTbl[id];
#if CFG_PAR_CHECKOUT_EN >0
	if(pecb->eventType != EVENT_TYPE_QUEUE) {
		return E_INVALID_ID;
	}
#endif
	pqcb = (P_QCB)pecb->eventPtr;
	if(pqcb->qSize == pqcb->qMaxSize) {
		return E_QUEUE_FULL;
	} else {
		OsSchedLock();
		*(pqcb->qStart + pqcb->tail) = pmail;
		pqcb->tail++;
		pqcb->qSize++;
		if(pqcb->tail == pqcb->qMaxSize) {
			pqcb->tail = 0;
		}
		EventTaskToRdy(pecb);
		OsSchedUnlock();
		return E_OK;
	}
}
