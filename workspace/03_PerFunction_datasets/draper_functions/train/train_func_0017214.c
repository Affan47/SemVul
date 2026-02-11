popFIFO(BUF_POS * b){
	Findex1 -- ;
	if (Findex1 < 0 ){
		return 0 ;
	}
	b->altitude = (FIFO1+Findex1)->altitude ;
	b->x = (FIFO1+Findex1)->x ;
	b->y = (FIFO1+Findex1)->y ;
	b->next= (FIFO1+Findex1)->next ;
	b->prev= (FIFO1+Findex1)->prev ;
	b->isit= (FIFO1+Findex1)->isit ;
	return 1;
}
