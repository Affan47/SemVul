copy_TBSCertificate(const TBSCertificate *from, TBSCertificate *to)
{
memset(to, 0, sizeof(*to));
{ int ret;
ret = der_copy_octet_string(&(from)->_save, &(to)->_save);
if (ret) goto fail;
}
if((from)->version) {
(to)->version = malloc(sizeof(*(to)->version));
if((to)->version == NULL) goto fail;
if(copy_Version((from)->version, (to)->version)) goto fail;
}else
(to)->version = NULL;
if(copy_CertificateSerialNumber(&(from)->serialNumber, &(to)->serialNumber)) goto fail;
if(copy_AlgorithmIdentifier(&(from)->signature, &(to)->signature)) goto fail;
if(copy_Name(&(from)->issuer, &(to)->issuer)) goto fail;
if(copy_Validity(&(from)->validity, &(to)->validity)) goto fail;
if(copy_Name(&(from)->subject, &(to)->subject)) goto fail;
if(copy_SubjectPublicKeyInfo(&(from)->subjectPublicKeyInfo, &(to)->subjectPublicKeyInfo)) goto fail;
if((from)->issuerUniqueID) {
(to)->issuerUniqueID = malloc(sizeof(*(to)->issuerUniqueID));
if((to)->issuerUniqueID == NULL) goto fail;
if(der_copy_bit_string((from)->issuerUniqueID, (to)->issuerUniqueID)) goto fail;
}else
(to)->issuerUniqueID = NULL;
if((from)->subjectUniqueID) {
(to)->subjectUniqueID = malloc(sizeof(*(to)->subjectUniqueID));
if((to)->subjectUniqueID == NULL) goto fail;
if(der_copy_bit_string((from)->subjectUniqueID, (to)->subjectUniqueID)) goto fail;
}else
(to)->subjectUniqueID = NULL;
if((from)->extensions) {
(to)->extensions = malloc(sizeof(*(to)->extensions));
if((to)->extensions == NULL) goto fail;
if(copy_Extensions((from)->extensions, (to)->extensions)) goto fail;
}else
(to)->extensions = NULL;
return 0;
fail:
free_TBSCertificate(to);
return ENOMEM;
}
