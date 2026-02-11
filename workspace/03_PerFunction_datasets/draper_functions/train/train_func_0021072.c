compute_invV_Y()
{

  const vnl_crs_index& crs = f_->residual_indices();

  typedef vnl_crs_index::sparse_vector::iterator sv_itr;

  for (int j=0; j<num_b_; ++j) {
    vnl_matrix<double>& inv_Vj = inv_V_[j];
    vnl_cholesky Vj_cholesky(V_[j],vnl_cholesky::quiet);

    if ( Vj_cholesky.rank_deficiency() > 0 )
    {
      vnl_svd<double> Vj_svd(V_[j]);
      inv_Vj = Vj_svd.inverse();
    }
    else
      inv_Vj = Vj_cholesky.inverse();

    vnl_crs_index::sparse_vector col = crs.sparse_col(j);
    for (sv_itr c_itr=col.begin(); c_itr!=col.end(); ++c_itr)
    {
      unsigned int k = c_itr->first;
      Y_[k] = W_[k]*inv_Vj;
    }
  }
}
