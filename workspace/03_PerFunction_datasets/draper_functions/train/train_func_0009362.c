prodNN(unsigned** pp,unsigned* end,int len){
	uint64_t prod = 1;

	unsigned* p = *pp;
	int count = 0;

	while(count < len){
		if(p >= end){
			*pp = end;
			return 0;
		}

		if(!*p){
			prod = 1;
			count = 0;
		}
		else{
			prod *= *p;
			count++;
		}
		p++;
	}


	*pp = (p-len);
	return prod;
}
