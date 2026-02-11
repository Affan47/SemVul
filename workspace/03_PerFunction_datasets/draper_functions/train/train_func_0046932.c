w1vect_getNode(struct w1_vect* v,int i){

	struct _w1Node* p = &(v->nodeZero);
	int count = 0;

	if(v->indOn){

		if( (v->indOn == AUTO) || (i<v->indLen) ){
			assert(i < v->indLen);
			return v->index[i];
		}
		else if(v->indLen){
			p = v->index[v->indLen-1];
			count = (v->indLen-1)*NODE_SIZE;
		}
	}

	while( count < i){
		count ++;
		p = p->next;
	}

	return p;
}
