get_seq_LCP(size_t i, TextIndex *csa, size_t **next_pos, size_t *n_next, bool dir) const{
		if(*n_next==0){
			*n_next = (size_t)rep->nLevels -1;
			for(size_t j=0; j< *n_next; j++)
				next_p[j] =0;
			*next_pos = next_p;
		}
		return (size_t)rep->access_seq(i+1, *next_pos, dir);
	}
