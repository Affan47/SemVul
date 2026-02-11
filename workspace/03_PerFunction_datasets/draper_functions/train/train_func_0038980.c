zx_DEC_ELEM_m20_SPDescriptor(struct zx_ctx* c, struct zx_m20_SPDescriptor_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_m20_KeyDescriptor_ELEM:
    if (!x->KeyDescriptor)
      x->KeyDescriptor = (struct zx_m20_KeyDescriptor_s*)el;
    return 1;
  case zx_m20_SoapEndpoint_ELEM:
    if (!x->SoapEndpoint)
      x->SoapEndpoint = el;
    return 1;
  case zx_m20_SingleLogoutServiceURL_ELEM:
    if (!x->SingleLogoutServiceURL)
      x->SingleLogoutServiceURL = el;
    return 1;
  case zx_m20_SingleLogoutServiceReturnURL_ELEM:
    if (!x->SingleLogoutServiceReturnURL)
      x->SingleLogoutServiceReturnURL = el;
    return 1;
  case zx_m20_FederationTerminationServiceURL_ELEM:
    if (!x->FederationTerminationServiceURL)
      x->FederationTerminationServiceURL = el;
    return 1;
  case zx_m20_FederationTerminationServiceReturnURL_ELEM:
    if (!x->FederationTerminationServiceReturnURL)
      x->FederationTerminationServiceReturnURL = el;
    return 1;
  case zx_m20_FederationTerminationNotificationProtocolProfile_ELEM:
    if (!x->FederationTerminationNotificationProtocolProfile)
      x->FederationTerminationNotificationProtocolProfile = el;
    return 1;
  case zx_m20_SingleLogoutProtocolProfile_ELEM:
    if (!x->SingleLogoutProtocolProfile)
      x->SingleLogoutProtocolProfile = el;
    return 1;
  case zx_m20_RegisterNameIdentifierProtocolProfile_ELEM:
    if (!x->RegisterNameIdentifierProtocolProfile)
      x->RegisterNameIdentifierProtocolProfile = el;
    return 1;
  case zx_m20_RegisterNameIdentifierServiceURL_ELEM:
    if (!x->RegisterNameIdentifierServiceURL)
      x->RegisterNameIdentifierServiceURL = el;
    return 1;
  case zx_m20_RegisterNameIdentifierServiceReturnURL_ELEM:
    if (!x->RegisterNameIdentifierServiceReturnURL)
      x->RegisterNameIdentifierServiceReturnURL = el;
    return 1;
  case zx_m20_NameIdentifierMappingProtocolProfile_ELEM:
    if (!x->NameIdentifierMappingProtocolProfile)
      x->NameIdentifierMappingProtocolProfile = el;
    return 1;
  case zx_m20_NameIdentifierMappingEncryptionProfile_ELEM:
    if (!x->NameIdentifierMappingEncryptionProfile)
      x->NameIdentifierMappingEncryptionProfile = el;
    return 1;
  case zx_m20_Organization_ELEM:
    if (!x->Organization)
      x->Organization = (struct zx_m20_Organization_s*)el;
    return 1;
  case zx_m20_ContactPerson_ELEM:
    if (!x->ContactPerson)
      x->ContactPerson = (struct zx_m20_ContactPerson_s*)el;
    return 1;
  case zx_m20_AdditionalMetaLocation_ELEM:
    if (!x->AdditionalMetaLocation)
      x->AdditionalMetaLocation = (struct zx_m20_AdditionalMetaLocation_s*)el;
    return 1;
  case zx_m20_Extension_ELEM:
    if (!x->Extension)
      x->Extension = (struct zx_m20_Extension_s*)el;
    return 1;
  case zx_ds_Signature_ELEM:
    if (!x->Signature)
      x->Signature = (struct zx_ds_Signature_s*)el;
    return 1;
  case zx_m20_AssertionConsumerServiceURL_ELEM:
    if (!x->AssertionConsumerServiceURL)
      x->AssertionConsumerServiceURL = (struct zx_m20_AssertionConsumerServiceURL_s*)el;
    return 1;
  case zx_m20_AuthnRequestsSigned_ELEM:
    if (!x->AuthnRequestsSigned)
      x->AuthnRequestsSigned = el;
    return 1;

  default: return 0;
  }
}
