output_density_images()
{
  Util::TimeMeter timeMeter;

  int n = basisInfo.noOfBasisFuncs;

  ergo_real* densityMatrixFull_tot  = new ergo_real[n*n];
  ergo_real* densityMatrixFull_spin = new ergo_real[n*n];


  {
    std::vector<ergo_real> densityMatrixFull_a(n*n);
    std::vector<ergo_real> densityMatrixFull_b(n*n);

    densityMatrix_alpha.readFromFile();
    densityMatrix_alpha.fullMatrix(densityMatrixFull_a,
				   matOpts.inversePermutationHML,
				   matOpts.inversePermutationHML);
    densityMatrix_alpha.writeToFile();

    densityMatrix_beta.readFromFile();
    densityMatrix_beta.fullMatrix(densityMatrixFull_b,
				  matOpts.inversePermutationHML,
				  matOpts.inversePermutationHML);
    densityMatrix_beta.writeToFile();

    for(int i = 0; i < n*n; i++)
      {
	densityMatrixFull_tot [i] = densityMatrixFull_a[i] + densityMatrixFull_b[i];
	densityMatrixFull_spin[i] = densityMatrixFull_a[i] - densityMatrixFull_b[i];
      }
  }

  do_density_images(basisInfo,
		    molecule,
		    densityMatrixFull_tot,
		    densityMatrixFull_spin,
		    scfopts.output_density_images_boxwidth);

  do_output(LOG_CAT_INFO, LOG_AREA_SCF, "SCF_unrestricted::output_density_images finished OK.");
  timeMeter.print(LOG_AREA_SCF, "SCF_unrestricted::output_density_images");
}
