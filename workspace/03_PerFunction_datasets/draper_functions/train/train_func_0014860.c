get_char_seq()
{
  CHECK_NOT_DESTROYED;

  if (prepareSequenceRead(CORBA::tk_char) == SEQ_HERE) {
    if (pd_n_in_buf < pd_first_in_comp)
      throw DynamicAny::DynAny::InvalidValue();

    CORBA::CharSeq_var seq = new CORBA::CharSeq(pd_n_components);
    seq->length(pd_n_components);
    CORBA::Char* data = seq->NP_data();

    if (pd_first_in_comp > 0) {
      pd_buf.rewindInputPtr();

      for (unsigned i=0; i < pd_first_in_comp; i++)
	data[i] = pd_buf.unmarshalChar();
    }
    for (unsigned i = pd_first_in_comp; i < pd_n_components; i++)
      data[i] = pd_components[i]->get_char();

    return seq._retn();
  }
  else {
    return getCurrent()->get_char_seq();
  }
}
