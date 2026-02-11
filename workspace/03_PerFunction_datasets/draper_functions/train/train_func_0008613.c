compute_Mb()
{

  const vnl_crs_index& crs = f_->residual_indices();

  typedef vnl_crs_index::sparse_vector::iterator sv_itr;

  vnl_matrix<double> temp;

  for (int j=0; j<num_b_; ++j)
  {
    temp.set_size(size_c_,f_->number_of_params_b(j));
    temp.fill(0.0);
    temp -= R_[j];

    vnl_crs_index::sparse_vector col = crs.sparse_col(j);
    for (sv_itr c_itr=col.begin(); c_itr!=col.end(); ++c_itr)
    {
      unsigned int k = c_itr->first;
      unsigned int i = c_itr->second;
      vnl_fastops::dec_X_by_AB(temp,Ma_[i],W_[k]);
    }
    vnl_fastops::AB(Mb_[j],temp,inv_V_[j]);
  }
}
