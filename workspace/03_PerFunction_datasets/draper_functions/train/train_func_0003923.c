JtJ(const NEWIMAGE::volume<float>&     ima1,
                                             const NEWIMAGE::volume<float>&     ima2,
                                             const NEWIMAGE::volume<char>       *mask,
                                             MISCMATHS::BFMatrixPrecisionType   prec)
const
{
  std::vector<unsigned int>  deriv(3,0);
  boost::shared_ptr<BFMatrix>  tmp = JtJ(deriv,ima1,ima2,mask,prec);
  return(tmp);
}
