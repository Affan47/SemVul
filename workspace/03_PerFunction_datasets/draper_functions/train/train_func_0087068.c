free_SignerInfo(SignerInfo *data)
{
free_CMSVersion(&(data)->version);
free_SignerIdentifier(&(data)->sid);
free_DigestAlgorithmIdentifier(&(data)->digestAlgorithm);
if((data)->signedAttrs) {
while(((data)->signedAttrs)->len){
free_Attribute(&((data)->signedAttrs)->val[((data)->signedAttrs)->len-1]);
((data)->signedAttrs)->len--;
}
free(((data)->signedAttrs)->val);
((data)->signedAttrs)->val = NULL;
free((data)->signedAttrs);
(data)->signedAttrs = NULL;
}
free_SignatureAlgorithmIdentifier(&(data)->signatureAlgorithm);
free_SignatureValue(&(data)->signature);
if((data)->unsignedAttrs) {
while(((data)->unsignedAttrs)->len){
free_Attribute(&((data)->unsignedAttrs)->val[((data)->unsignedAttrs)->len-1]);
((data)->unsignedAttrs)->len--;
}
free(((data)->unsignedAttrs)->val);
((data)->unsignedAttrs)->val = NULL;
free((data)->unsignedAttrs);
(data)->unsignedAttrs = NULL;
}
}
