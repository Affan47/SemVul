NSibling(size_t vl, size_t vr, size_t *nsibling_l, size_t *nsibling_r) const{
		size_t wl, wr;
		Parent(vl, vr, &wl, &wr);
		if(wl==(size_t)-1){
			*nsibling_l = (size_t)-1;
			*nsibling_r = (size_t)-1;
			return;
		}
		if(wr == vr){
			*nsibling_l = (size_t)-1;
			*nsibling_r = (size_t)-1;
			return;
		}
		if(vr+1 == wr){
			*nsibling_l = wr;
			*nsibling_r = wr;
			return;
		}
		else{
			size_t left = vr+1;
			size_t lcp_rm = lcp->get_LCP(vr+1, csa);
			size_t rm =  npr->fwd_NSV(vr+1, csa, lcp, lcp_rm+1);
			*nsibling_l = left;
			*nsibling_r = rm-1;
			return;
		}
	}
