JtJ(const NEWIMAGE::volume<float>&     ima,
                                             const NEWIMAGE::volume<char>       *mask,
                                             MISCMATHS::BFMatrixPrecisionType   prec)
const
{
  std::vector<unsigned int>  deriv(3,0);
  boost::shared_ptr<BFMatrix>  tmp = JtJ(deriv,ima,ima,mask,prec);
  return(tmp);
}
