get_2e_matrix_and_energy_simple_HF_sparse(const BasisInfoStruct& basisInfo,
					  const Molecule& molecule,
					  const IntegralInfo& integralInfo,
					  const JK::ExchWeights & CAM_params,
					  symmMatrix & twoelMatrix_sparse,
					  symmMatrix & densityMatrix_sparse,
					  const JK::Params& J_K_params,
					  mat::SizesAndBlocks const & matrix_size_block_info,
					  std::vector<int> const & permutationHML,
					  std::vector<int> const & inversePermutationHML,
					  ergo_real* energy_2el,
					  int get_J_K_matrices,
					  symmMatrix & J_matrix,
					  symmMatrix & K_matrix)
{

  symmMatrix J;
  J.resetSizesAndBlocks(matrix_size_block_info,
			       matrix_size_block_info);
  symmMatrix K;
  K.resetSizesAndBlocks(matrix_size_block_info,
			       matrix_size_block_info);

  if(compute_J_by_boxes_sparse(basisInfo,
			       integralInfo,
			       J_K_params,
			       J,
			       densityMatrix_sparse,
			       permutationHML) != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_SCF, "error in compute_J_by_boxes_sparse");
      return -1;
    }


  if(compute_K_by_boxes_sparse(basisInfo,
			       integralInfo,
			       CAM_params,
			       J_K_params,
			       K,
			       densityMatrix_sparse,
			       permutationHML,
			       inversePermutationHML) != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_SCF, "error in compute_K_by_boxes_sparse");
      return -1;
    }

  twoelMatrix_sparse = J + K;
  if ( get_J_K_matrices == 1 ) {
    do_output(LOG_CAT_INFO, LOG_AREA_SCF, "Saving J and K matrices as requested.");
    J_matrix = J;
    K_matrix = K;
  }

  *energy_2el = 0.5 * symmMatrix::trace_ab(densityMatrix_sparse, twoelMatrix_sparse);

  return 0;
}
