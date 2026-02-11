free_DigestRepInner(DigestRepInner *data)
{
switch((data)->element) {
case choice_DigestRepInner_error:
free_DigestError(&(data)->u.error);
break;
case choice_DigestRepInner_initReply:
free_DigestInitReply(&(data)->u.initReply);
break;
case choice_DigestRepInner_response:
free_DigestResponse(&(data)->u.response);
break;
case choice_DigestRepInner_ntlmInitReply:
free_NTLMInitReply(&(data)->u.ntlmInitReply);
break;
case choice_DigestRepInner_ntlmResponse:
free_NTLMResponse(&(data)->u.ntlmResponse);
break;
case choice_DigestRepInner_supportedMechs:
free_DigestTypes(&(data)->u.supportedMechs);
break;
case choice_DigestRepInner_asn1_ellipsis:
der_free_octet_string(&(data)->u.asn1_ellipsis);
break;}
}
