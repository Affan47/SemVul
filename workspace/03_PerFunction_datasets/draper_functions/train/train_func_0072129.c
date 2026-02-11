aq_find(aqd)

QUEUE			*aqd;

{


	if (aqd->aq_nelem <= 0) {
		return((void *) 0);
	}
	else {
		return((void *) (((char *) aqd->aq_queue) +
			(aqd->aq_first * aqd->aq_elemsize)));
	}
}
