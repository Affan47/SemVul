create_first_level(LCP *lcp, TextIndex *csa){
		uint *P_aux;
		uint *R_aux;

		uint size = (n+W-1)/W;
		uint last_psv = n;
		uint j, lcp_value, psv_aux;
		P_aux = new uint[size];
		R_aux = new uint[size];

		for(uint i=0; i<size; i++){
				P_aux[i]=0;
				R_aux[i]=0;
		}

		for(uint i=n; i>0; i--){
			lcp_value = lcp->get_LCP(i-1,csa);
			psv_aux = 0;
			for(j=i-1; j>0; j--){
				psv_aux =  lcp->get_LCP(j-1,csa);
				if(lcp_value > psv_aux){

					if( i/b !=  j/b ){
						if( j/b != last_psv/b){

							bitset(P_aux,i);

							bitset(R_aux,i);
							bitset(R_aux,j);
						}
						last_psv=j;
					}
					break;
				}
			}
			if(j==0){
				 if( i/b != j/b ){
					 if( j/b !=  last_psv/b){

						 bitset(P_aux,i);

						 bitset(R_aux,i);
						 bitset(R_aux,j);
					 }
					 last_psv=j;
				 }
			}
		}
		P[0] = new BitSequenceRRR(P_aux, n+1);
		R[0] = new BitSequenceRRR(R_aux, n+1);
		delete[] P_aux;
		delete[] R_aux;
	}
