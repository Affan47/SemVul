fastMarshalChar(cdrStream&          stream,
			   omniCodeSet::NCS_C* ncs,
			   CORBA::Char         c)
{
  if (ncs->id() == id()) {
    stream.marshalOctet(c);
    return 1;
  }
  return 0;
}
