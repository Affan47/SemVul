nssCertificateStore_FindCertificatesByEmail (
  nssCertificateStore *store,
  NSSASCII7 *email,
  NSSCertificate *rvOpt[],
  PRUint32 maximumOpt,
  NSSArena *arenaOpt
)
{
    NSSCertificate **rvArray = NULL;
    struct email_template_str et;
    et.email = email;
    et.emailList = nssList_Create(NULL, PR_FALSE);
    if (!et.emailList) {
	return NULL;
    }
    PZ_Lock(store->lock);
    nssHash_Iterate(store->subject, match_email, &et);
    if (et.emailList) {

	nssCertificateList_AddReferences(et.emailList);
    }
    PZ_Unlock(store->lock);
    if (et.emailList) {
	rvArray = get_array_from_list(et.emailList,
	                              rvOpt, maximumOpt, arenaOpt);
	nssList_Destroy(et.emailList);
    }
    return rvArray;
}
