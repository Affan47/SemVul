reech_chi2(int sum_case, int sum_control, int nb_nodes,
		      int chi2_reel, const struct cc *nodes, struct cc *th)
{
	int sum_total=sum_case+sum_control;
	datatype_t p_val=0.0;

	int i,k;
	for(i=0; i<nb_nodes; i++) {
		th[i].controls=((datatype_t)(sum_control*(nodes[i].cases+nodes[i].controls)))/sum_total;
		th[i].cases=((datatype_t)(sum_case*(nodes[i].cases+nodes[i].controls)))/sum_total;
	}

	struct cc clades[nb_nodes];
	for (k=1;k<=PERM; k++){
		random_clades(nb_nodes, nodes, sum_case, sum_control, clades);

		datatype_t chi2=0.0;
		for(i=0; i<nb_nodes; i++) {
			datatype_t t;
			t=clades[i].cases - th[i].cases;
			chi2 += t*t/th[i].cases;
			t=clades[i].controls - th[i].controls;
			chi2 += t*t/th[i].controls;
		}
		if (chi2 >= chi2_reel){
			p_val++;
		}
	}

	return (p_val/PERM);
}
