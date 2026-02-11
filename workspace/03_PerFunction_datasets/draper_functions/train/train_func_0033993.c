dmatvec ( ldm, nrow, ncol, M, vec, Mxvec )

int ldm;
int nrow;
int ncol;
double *M;
double *vec;
double *Mxvec;

{
    double vi0, vi1, vi2, vi3, vi4, vi5, vi6, vi7;
    double *M0;
    register double *Mki0, *Mki1, *Mki2, *Mki3, *Mki4, *Mki5, *Mki6, *Mki7;
    register int firstcol = 0;
    int k;

    M0 = &M[0];
    while ( firstcol < ncol - 7 ) {

	Mki0 = M0;
	Mki1 = Mki0 + ldm;
        Mki2 = Mki1 + ldm;
        Mki3 = Mki2 + ldm;
	Mki4 = Mki3 + ldm;
	Mki5 = Mki4 + ldm;
	Mki6 = Mki5 + ldm;
	Mki7 = Mki6 + ldm;

	vi0 = vec[firstcol++];
	vi1 = vec[firstcol++];
	vi2 = vec[firstcol++];
	vi3 = vec[firstcol++];
	vi4 = vec[firstcol++];
	vi5 = vec[firstcol++];
	vi6 = vec[firstcol++];
	vi7 = vec[firstcol++];

	for (k = 0; k < nrow; k++)
	    Mxvec[k] += vi0 * *Mki0++ + vi1 * *Mki1++
		      + vi2 * *Mki2++ + vi3 * *Mki3++
		      + vi4 * *Mki4++ + vi5 * *Mki5++
		      + vi6 * *Mki6++ + vi7 * *Mki7++;

	M0 += 8 * ldm;
    }

    while ( firstcol < ncol - 3 ) {

	Mki0 = M0;
	Mki1 = Mki0 + ldm;
	Mki2 = Mki1 + ldm;
	Mki3 = Mki2 + ldm;

	vi0 = vec[firstcol++];
	vi1 = vec[firstcol++];
	vi2 = vec[firstcol++];
	vi3 = vec[firstcol++];
	for (k = 0; k < nrow; k++)
	    Mxvec[k] += vi0 * *Mki0++ + vi1 * *Mki1++
		      + vi2 * *Mki2++ + vi3 * *Mki3++ ;

	M0 += 4 * ldm;
    }

    while ( firstcol < ncol ) {

 	Mki0 = M0;
	vi0 = vec[firstcol++];
	for (k = 0; k < nrow; k++)
	    Mxvec[k] += vi0 * *Mki0++;

	M0 += ldm;
    }

}
