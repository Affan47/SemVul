free_DigestReqInner(DigestReqInner *data)
{
switch((data)->element) {
case choice_DigestReqInner_init:
free_DigestInit(&(data)->u.init);
break;
case choice_DigestReqInner_digestRequest:
free_DigestRequest(&(data)->u.digestRequest);
break;
case choice_DigestReqInner_ntlmInit:
free_NTLMInit(&(data)->u.ntlmInit);
break;
case choice_DigestReqInner_ntlmRequest:
free_NTLMRequest(&(data)->u.ntlmRequest);
break;
case choice_DigestReqInner_supportedMechs:
break;
}
}
