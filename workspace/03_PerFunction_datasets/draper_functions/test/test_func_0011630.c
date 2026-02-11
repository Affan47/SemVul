allocate_matrices()
{

  const vnl_crs_index& crs = f_->residual_indices();

  typedef vnl_crs_index::sparse_vector::iterator sv_itr;


  for (int i=0; i<num_a_; ++i)
  {
    const unsigned int ai_size = f_->number_of_params_a(i);
    U_[i].set_size(ai_size,ai_size);
    Q_[i].set_size(size_c_, ai_size);
    Z_[i].set_size(size_c_, ai_size);
    Ma_[i].set_size(size_c_, ai_size);

    vnl_crs_index::sparse_vector row = crs.sparse_row(i);
    for (sv_itr r_itr=row.begin(); r_itr!=row.end(); ++r_itr)
    {
      const unsigned int j = r_itr->second;
      const unsigned int k = r_itr->first;
      const unsigned int bj_size = f_->number_of_params_b(j);
      const unsigned int eij_size = f_->number_of_residuals(k);
      A_[k].set_size(eij_size, ai_size);
      B_[k].set_size(eij_size, bj_size);
      C_[k].set_size(eij_size, size_c_);
      W_[k].set_size(ai_size, bj_size);
      Y_[k].set_size(ai_size, bj_size);
    }
  }
  for (int j=0; j<num_b_; ++j)
  {
    const unsigned int bj_size = f_->number_of_params_b(j);
    V_[j].set_size(bj_size,bj_size);
    R_[j].set_size(size_c_, bj_size);
    Mb_[j].set_size(size_c_, bj_size);
    inv_V_[j].set_size(bj_size,bj_size);
  }
}
