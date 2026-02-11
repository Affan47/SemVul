compute_normal_equations()
{

  const vnl_crs_index& crs = f_->residual_indices();

  typedef vnl_crs_index::sparse_vector::iterator sv_itr;


  ea_.fill(0.0);
  eb_.fill(0.0);
  ec_.fill(0.0);

  for (unsigned int j=0; j<f_->number_of_b(); ++j)
  {
    V_[j].fill(0.0);
    R_[j].fill(0.0);
  }
  T_.fill(0.0);


  for (unsigned int i=0; i<f_->number_of_a(); ++i)
  {
    vnl_matrix<double>& Ui = U_[i];
    Ui.fill(0.0);
    vnl_matrix<double>& Qi = Q_[i];
    Qi.fill(0.0);
    unsigned int ai_size = f_->number_of_params_a(i);
    vnl_vector_ref<double> eai(ai_size, ea_.data_block()+f_->index_a(i));

    vnl_crs_index::sparse_vector row = crs.sparse_row(i);
    for (sv_itr r_itr=row.begin(); r_itr!=row.end(); ++r_itr)
    {
      unsigned int j = r_itr->second;
      unsigned int k = r_itr->first;;
      vnl_matrix<double>& Aij = A_[k];
      vnl_matrix<double>& Bij = B_[k];
      vnl_matrix<double>& Cij = C_[k];
      vnl_matrix<double>& Vj = V_[j];
      vnl_matrix<double>& Rj = R_[j];
      vnl_vector_ref<double> ebj(Bij.cols(), eb_.data_block()+f_->index_b(j));

      vnl_fastops::inc_X_by_AtA(T_, Cij);
      vnl_fastops::inc_X_by_AtA(Ui,Aij);
      vnl_fastops::inc_X_by_AtA(Vj,Bij);
      vnl_fastops::AtB(W_[k],Aij,Bij);
      vnl_fastops::inc_X_by_AtB(Qi,Cij,Aij);
      vnl_fastops::inc_X_by_AtB(Rj,Cij,Bij);

      vnl_vector_ref<double> eij(f_->number_of_residuals(k), e_.data_block()+f_->index_e(k));
      vnl_fastops::inc_X_by_AtB(eai,Aij,eij);
      vnl_fastops::inc_X_by_AtB(ebj,Bij,eij);
      vnl_fastops::inc_X_by_AtB(ec_,Cij,eij);
    }
  }
}
