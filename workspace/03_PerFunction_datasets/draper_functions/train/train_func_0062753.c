vl_svm_l1_loss_derivative (double inner, double label)
{
  if (label > inner) {
    return - 1.0 ;
  } else {
    return + 1.0 ;
  }
}
