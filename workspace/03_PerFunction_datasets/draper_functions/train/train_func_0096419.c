free_unknown_poss() {
  int curr_person, locus, loop_v;

  if (unknown_poss != NULL) {
    for (curr_person = 1; curr_person <= totperson; curr_person++){

       if ( person[curr_person]->unknown ) {
	for (locus = 0; locus < mlocus; locus++){
	  if ( person[curr_person]->thisunknown[locus] ) {
	    for (loop_v = 0; loop_v < num_loop_vectors[locus]; loop_v++) {
	      free(unknown_poss[curr_person][locus][loop_v]);
	    }
	  } else {
	    free(unknown_poss[curr_person][locus][0]);
	  }
	  free(unknown_poss[curr_person][locus]);
	}
	free(unknown_poss[curr_person]);
	person[curr_person]->unknown = false;
      }
    }
    free(unknown_poss);
    unknown_poss = NULL;
  }
}
