add_random_disturbance_to_starting_guess()
{
  if(scfopts.sg_disturb_specific_elements > SCF::DISTURB_ELEMENT_MAX_COUNT)
    throw "Error in SCF_unrestricted::add_random_disturbance_to_starting_guess: (scfopts.sg_disturb_specific_elements > SCF::DISTURB_ELEMENT_MAX_COUNT)";
  int n = basisInfo.noOfBasisFuncs;
  densityMatrix_alpha.readFromFile();
  do_output(LOG_CAT_INFO, LOG_AREA_SCF,
	    "SCF_unrestricted::add_random_disturbance_to_starting_guess, scfopts.starting_guess_disturbance = %7.3f",
	    scfopts.starting_guess_disturbance);
  add_disturbance_to_matrix(n,
			    densityMatrix_alpha,
			    scfopts.starting_guess_disturbance,
			    scfopts.sg_disturb_specific_elements,
			    scfopts.disturbedElementIndexVector,
			    matOpts.permutationHML);
  densityMatrix_alpha.writeToFile();
  densityMatrix_beta.readFromFile();
  add_disturbance_to_matrix(n,
			    densityMatrix_beta ,
			    -1 * scfopts.starting_guess_disturbance,
			    scfopts.sg_disturb_specific_elements,
			    scfopts.disturbedElementIndexVector,
			    matOpts.permutationHML);
  densityMatrix_beta.writeToFile();
}
