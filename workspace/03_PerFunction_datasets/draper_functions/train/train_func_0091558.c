symm_orth(Matrix &Mat)
{
  SymmetricMatrix Metric;
  Metric << Mat.t()*Mat;
  Metric = Metric.i();
  Matrix tmpE;
  DiagonalMatrix tmpD;
  EigenValues(Metric,tmpD,tmpE);
  Mat = Mat * tmpE * sqrt(abs(tmpD)) * tmpE.t();
}
