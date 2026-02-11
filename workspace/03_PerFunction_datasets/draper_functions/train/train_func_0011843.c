apply_weights(vnl_vector<double> const& weights,
                                           vnl_vector<double>& e)
{
  typedef vnl_crs_index::sparse_vector::iterator sv_itr;
  for (unsigned int i=0; i<number_of_a(); ++i)
  {
    vnl_crs_index::sparse_vector row = residual_indices_.sparse_row(i);
    for (sv_itr r_itr=row.begin(); r_itr!=row.end(); ++r_itr)
    {
      unsigned int j = r_itr->second;
      unsigned int k = r_itr->first;
      vnl_vector_ref<double> eij(number_of_residuals(k), e.data_block()+index_e(k));
      apply_weight_ij(i,j,weights[k],eij);
    }
  }
}
