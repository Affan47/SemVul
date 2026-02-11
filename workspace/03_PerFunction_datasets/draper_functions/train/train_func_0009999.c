unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();
  arg_1_ = new CosTrading::PropertyNameSeq;
  (CosTrading::PropertyNameSeq&)arg_1_ <<= _n;
  arg_1 = &arg_1_.in();
  arg_2_ = new CosTrading::PropertySeq;
  (CosTrading::PropertySeq&)arg_2_ <<= _n;
  arg_2 = &arg_2_.in();

}
