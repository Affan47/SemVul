getSize() const{

		size_t size =0;
		size +=  sizeof(NSV);
		for(size_t i=0; i<r; i++){
			size += R[i]->getSize() + P[i]->getSize();
		}
		size +=  ((b_A*R[r-1]->rank1(n-1) + W -1)/W)*sizeof(uint);
		return size;
	}
