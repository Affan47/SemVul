zx_DEC_ELEM_di12_Description(struct zx_ctx* c, struct zx_di12_Description_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_di12_SecurityMechID_ELEM:
    if (!x->SecurityMechID)
      x->SecurityMechID = el;
    return 1;
  case zx_di12_CredentialRef_ELEM:
    if (!x->CredentialRef)
      x->CredentialRef = el;
    return 1;
  case zx_di12_WsdlURI_ELEM:
    if (!x->WsdlURI)
      x->WsdlURI = el;
    return 1;
  case zx_di12_ServiceNameRef_ELEM:
    if (!x->ServiceNameRef)
      x->ServiceNameRef = el;
    return 1;
  case zx_di12_Endpoint_ELEM:
    if (!x->Endpoint)
      x->Endpoint = el;
    return 1;
  case zx_di12_SoapAction_ELEM:
    if (!x->SoapAction)
      x->SoapAction = el;
    return 1;

  default: return 0;
  }
}
