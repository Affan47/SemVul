nssToken_ImportCRL (
  NSSToken *token,
  nssSession *sessionOpt,
  NSSDER *subject,
  NSSDER *encoding,
  PRBool isKRL,
  NSSUTF8 *url,
  PRBool asTokenObject
)
{
    nssCryptokiObject *object;
    CK_OBJECT_CLASS crlobjc = CKO_NSS_CRL;
    CK_ATTRIBUTE_PTR attr;
    CK_ATTRIBUTE crl_tmpl[6];
    CK_ULONG crlsize;

    NSS_CK_TEMPLATE_START(crl_tmpl, attr, crlsize);
    if (asTokenObject) {
	NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_TOKEN, &g_ck_true);
    } else {
	NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_TOKEN, &g_ck_false);
    }
    NSS_CK_SET_ATTRIBUTE_VAR( attr, CKA_CLASS,        crlobjc);
    NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_SUBJECT,      subject);
    NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_VALUE,        encoding);
    NSS_CK_SET_ATTRIBUTE_UTF8(attr, CKA_NSS_URL, url);
    if (isKRL) {
	NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_NSS_KRL, &g_ck_true);
    } else {
	NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_NSS_KRL, &g_ck_false);
    }
    NSS_CK_TEMPLATE_FINISH(crl_tmpl, attr, crlsize);


    object = import_object(token, sessionOpt, crl_tmpl, crlsize);
    if (object && token->cache) {
	nssTokenObjectCache_ImportObject(token->cache, object, crlobjc,
	                                 crl_tmpl, crlsize);
    }
    return object;
}
