operator<<= (cdrStream& s)
{
  PR_clearData();

  pd_tc   = CORBA::TypeCode::unmarshalTypeCode(s);
  pd_mbuf = new cdrAnyMemoryStream;
  tcParser::copyStreamToStream(get(pd_tc), s, *pd_mbuf);
}
