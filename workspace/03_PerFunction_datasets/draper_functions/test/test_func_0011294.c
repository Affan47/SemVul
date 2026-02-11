zxid_saml2_map_protocol_binding(const char* b)
{
  switch (b[0]) {
  case 'r' : return SAML2_REDIR;
  case 'a' :   return SAML2_ART;
  case 'p' :  return SAML2_POST;
  case 'q' :  return SAML2_POST_SIMPLE_SIGN;
  case 's' :  return SAML2_SOAP;
  case 'e' :
      return SAML2_PAOS;
  default:      return b;
  }
}
