compute_stressf(float **coords, float *lap, int dim, int n, int exp)
{


    int i, j, l, neighbor, count;
    double sum, dist, Dij;
    sum = 0;
    for (count = 0, i = 0; i < n - 1; i++) {
	count++;
	for (j = 1; j < n - i; j++, count++) {
	    dist = 0;
	    neighbor = i + j;
	    for (l = 0; l < dim; l++) {
		dist +=
		    (coords[l][i] - coords[l][neighbor]) * (coords[l][i] -
							    coords[l]
							    [neighbor]);
	    }
	    dist = sqrt(dist);
	    if (exp == 2) {
#ifdef Dij2
		Dij = 1.0 / sqrt(lap[count]);
		sum += (Dij - dist) * (Dij - dist) * (lap[count]);
#else
		Dij = 1.0 / lap[count];
		sum += (Dij - dist) * (Dij - dist) * (lap[count]);
#endif
	    } else {
		Dij = 1.0 / lap[count];
		sum += (Dij - dist) * (Dij - dist) * (lap[count]);
	    }
	}
    }

    return sum;
}
