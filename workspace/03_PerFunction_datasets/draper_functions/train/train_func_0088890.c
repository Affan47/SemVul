RemoveFromTCBRdyList(P_OSTCB ptcb) {

#if CFG_ORDER_LIST_SCHEDULE_EN ==0
	U8 prio;
	U8 seqNum;
	BOOL isChange;
	isChange = Co_FALSE;
	prio = ptcb->prio;
	GetPriSeqNum(prio,&seqNum);
#endif


	if((ptcb->TCBnext == Co_NULL) && (ptcb->TCBprev == Co_NULL) ) {
		TCBRdy = Co_NULL;
#if CFG_ORDER_LIST_SCHEDULE_EN ==0
		isChange = Co_TRUE;
#endif
	} else if(ptcb->TCBprev == Co_NULL) {

		TCBRdy = ptcb->TCBnext;
		ptcb->TCBnext   = Co_NULL;
		TCBRdy->TCBprev = Co_NULL;
#if CFG_ORDER_LIST_SCHEDULE_EN ==0
		if(TCBRdy->prio != prio) {
			isChange = Co_TRUE;
		}

#endif
	} else if( ptcb->TCBnext == Co_NULL) {

#if CFG_ORDER_LIST_SCHEDULE_EN ==0
		if(ptcb->TCBprev->prio != prio) {
			isChange = Co_TRUE;
		} else {
			RdyTaskPri[seqNum] = ptcb->TCBprev->taskID;
		}
#endif
		ptcb->TCBprev->TCBnext = Co_NULL;
		ptcb->TCBprev          = Co_NULL;
	} else {
#if CFG_ORDER_LIST_SCHEDULE_EN ==0
		if((ptcb->TCBprev->prio != prio) && (ptcb->TCBnext->prio != prio)) {
			isChange = Co_TRUE;
		} else if((ptcb->TCBprev->prio == prio) && (ptcb->TCBnext->prio != prio)) {
			RdyTaskPri[seqNum] = ptcb->TCBprev->taskID;
		}
#endif
		ptcb->TCBprev->TCBnext = ptcb->TCBnext;
		ptcb->TCBnext->TCBprev = ptcb->TCBprev;
		ptcb->TCBnext = Co_NULL;
		ptcb->TCBprev = Co_NULL;
	}
#if CFG_ORDER_LIST_SCHEDULE_EN ==0
	if(isChange == Co_TRUE) {
		RdyTaskPri[seqNum] = INVALID_ID;
		SetPrioSeqNumStatus(seqNum, 0);
	}
#endif
}
