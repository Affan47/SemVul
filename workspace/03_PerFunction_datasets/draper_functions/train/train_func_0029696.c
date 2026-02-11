print_search(graph_t *g) {
	fprintf(stderr,"Searching for %s ",find_all?"all":"a single");
	if (min_weight==0) {
		fprintf(stderr,"maximum %s clique%s...\n",
			unweighted?"size":"weight",find_all?"s":"");
		return;
	}
	if (min_weight>0 && maximal)
		fprintf(stderr,"maximal ");
	fprintf(stderr,"clique%s with %s ",find_all?"s":"",
		unweighted?"size":"weight");
	if (max_weight==0) {
		fprintf(stderr,"at least %d...",min_weight);
	} else if (min_weight==max_weight) {
		fprintf(stderr,"exactly %d...",min_weight);
	} else {
		fprintf(stderr,"within range %d-%d...",min_weight,max_weight);
	}
	fprintf(stderr,"\n");
	return;
}
