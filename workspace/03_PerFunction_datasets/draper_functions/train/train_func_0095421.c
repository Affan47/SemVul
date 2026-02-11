unmarshal_TAG_CODE_SETS(const IOP::TaggedComponent& c, omniIOR& ior)
{
  OMNIORB_ASSERT(c.tag == IOP::TAG_CODE_SETS);
  cdrEncapsulationStream e(c.component_data.get_buffer(),
			   c.component_data.length(),1);

  CONV_FRAME::CodeSetComponentInfo info;
  info <<= e;


  omniCodeSet::TCS_C* tcs_c = 0;
  if (info.ForCharData.native_code_set) {
    tcs_c = omniCodeSet::getTCS_C(info.ForCharData.native_code_set,
				  ior.getIORInfo()->version());
  }
  if (!tcs_c) {
    CORBA::ULong total = info.ForCharData.conversion_code_sets.length();
    for (CORBA::ULong index=0; index < total; index++) {
      tcs_c = omniCodeSet::getTCS_C(
		      info.ForCharData.conversion_code_sets[index],
		      ior.getIORInfo()->version());
      if (tcs_c) break;
    }
  }
  if (!tcs_c && (info.ForCharData.native_code_set ||
		 info.ForCharData.conversion_code_sets.length())) {


    tcs_c = omniCodeSet::getTCS_C(omniCodeSet::ID_UTF_8,
				  ior.getIORInfo()->version());
  }
  ior.getIORInfo()->TCS_C(tcs_c);


  omniCodeSet::TCS_W* tcs_w = 0;
  if (info.ForWcharData.native_code_set) {
    tcs_w = omniCodeSet::getTCS_W(info.ForWcharData.native_code_set,
				  ior.getIORInfo()->version());
  }
  if (!tcs_w) {
    CORBA::ULong total = info.ForWcharData.conversion_code_sets.length();
    for (CORBA::ULong index=0; index < total; index++) {
      tcs_w = omniCodeSet::getTCS_W(
		       info.ForWcharData.conversion_code_sets[index],
		       ior.getIORInfo()->version());
      if (tcs_w) break;
    }
  }
  if (!tcs_w && (info.ForWcharData.native_code_set ||
		 info.ForWcharData.conversion_code_sets.length())) {


    tcs_w = omniCodeSet::getTCS_W(omniCodeSet::ID_UTF_16,
				  ior.getIORInfo()->version());
  }
  ior.getIORInfo()->TCS_W(tcs_w);
}
