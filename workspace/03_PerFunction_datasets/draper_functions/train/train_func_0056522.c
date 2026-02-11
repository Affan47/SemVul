query(const char* type, const char* constr, const char* pref, const ::CosTrading::PolicySeq& policies, const ::CosTrading::Lookup::SpecifiedProps& desired_props, ::CORBA::ULong how_many, ::CosTrading::OfferSeq_out offers, ::CosTrading::OfferIterator_out offer_itr, ::CosTrading::PolicyNameSeq_out limits_applied)
{
  _0RL_cd_6b2f9da8b63bbcbb_e1000000 _call_desc(_0RL_lcfn_6b2f9da8b63bbcbb_f1000000, "query", 6);
  _call_desc.arg_0 = type;
  _call_desc.arg_1 = constr;
  _call_desc.arg_2 = pref;
  _call_desc.arg_3 = &(::CosTrading::PolicySeq&) policies;
  _call_desc.arg_4 = &(::CosTrading::Lookup::SpecifiedProps&) desired_props;
  _call_desc.arg_5 = how_many;

  _invoke(_call_desc);
  offers = _call_desc.arg_6._retn();
  offer_itr = _call_desc.arg_7._retn();
  limits_applied = _call_desc.arg_8._retn();


}
