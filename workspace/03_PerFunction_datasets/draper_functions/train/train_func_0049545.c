IsSquareProblem() const
  {
    return (ip_data_->curr()->x()->Dim() == ip_data_->curr()->y_c()->Dim());
  }
