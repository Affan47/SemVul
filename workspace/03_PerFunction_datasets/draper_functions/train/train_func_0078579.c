choose_best(struct matrix *m, int * best_i, int * best_j, int istart, int iend, int jstart, int jend )
{
	int i, j;
	double best_score = 0;


	*best_i = istart;
	*best_j = jstart;


	if(jstart!=jend) {
		for (i=m->width, j=jstart; j <= jend; j++) {
			if ( matrix(m,i,j).score > best_score) {
	      			best_score =  matrix(m,i,j).score;
	      			*best_i = i;
	      			*best_j = j;
			}
		}
	}


	if(istart!=iend) {
		for (i=istart, j=m->height; i <= iend; i++) {
			if ( matrix(m,i,j).score > best_score) {
				best_score =  matrix(m,i,j).score;
				*best_i = i;
				*best_j = j;
			}
		}
	}
}
