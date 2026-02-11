pt_in_rect(NODE * node,BOX * b){
	int x = node->x,y=node->y;
	NODE * ll = &b->ll;
	NODE * ur = &b->ur;
	if( (x<ur->x && x>ll->x) &&
	    (y<ur->y && y>ll->y) ){
#ifdef DEBUG
		printf("(%d,%d) sec (%d %d),(%d %d)\n",x,y,
				ll->x,ll->y,
				ur->x,ur->y);
#endif
		return TRUE;
	}
	return FALSE;
}
