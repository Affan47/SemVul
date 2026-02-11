zxid_new_epr(zxid_conf* cf, char* address, char* desc, char* entid, char* svctype)
{
  zxid_epr* epr = zx_NEW_a_EndpointReference(cf->ctx,0);
  if (address) {
    epr->Address = zx_NEW_a_Address(cf->ctx, &epr->gg);
    zx_add_content(cf->ctx, &epr->Address->gg, zx_dup_str(cf->ctx, address));
  }
  if (desc || entid || svctype) {
    epr->Metadata = zx_NEW_a_Metadata(cf->ctx, &epr->gg);
    if (desc)
      epr->Metadata->Abstract
	= zx_dup_elem(cf->ctx, &epr->Metadata->gg, zx_di_Abstract_ELEM, desc);
    if (entid)
      epr->Metadata->ProviderID
	= zx_dup_elem(cf->ctx, &epr->Metadata->gg, zx_di_ProviderID_ELEM, entid);
    if (svctype)
      epr->Metadata->ServiceType
	= zx_dup_elem(cf->ctx, &epr->Metadata->gg, zx_di_ServiceType_ELEM, svctype);
  }
  return epr;
}
