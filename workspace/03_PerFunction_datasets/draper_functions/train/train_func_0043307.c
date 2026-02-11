upl(int off){
		int retval;

		while((retval=gnn())==0){
			off++;
		};
		while(off-->0){
			retval=retval<<4;
			retval+=gnn();
		};
		return retval;
	}
