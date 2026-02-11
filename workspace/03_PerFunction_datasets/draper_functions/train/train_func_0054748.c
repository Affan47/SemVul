LAQt(size_t vl, size_t vr, size_t d, size_t *laq_t_l, size_t *laq_t_r) const{
		size_t depth = 0;
		size_t x;
		size_t string_depth = d;
		size_t res_l, res_r;
		size_t next_l, next_r;
		size_t aux_l, aux_r;
		size_t acum =1;
		if(d==0 || (vl==0 && vr==length-1)){
			*laq_t_l = 0;
			*laq_t_r = length-1;
			return;
		}
		LAQs(vl, vr, d, &res_l, &res_r);
		depth = TDepth(res_l, res_r);
		x = d-depth;
		while(x!=0 && !(res_l==vl && res_r==vr) ){
			if(acum==1)
				string_depth = SDepth(res_l,res_r);
			LAQs(vl, vr, string_depth+x, &next_l, &next_r);
			aux_l = next_l;
			aux_r = next_r;

			while(aux_l != res_l || aux_r != res_r){
					Parent(aux_l, aux_r, &aux_l, &aux_r);
					depth++;
			}

			if(res_l==next_l && res_r==next_r){
				string_depth++;
				acum++;
			}
			else{
				acum = 1;
				res_l = next_l;
				res_r = next_r;
				x = d - depth;
			}
		}
		*laq_t_l = res_l;
		*laq_t_r = res_r;
	}
