decode_PA_FX_FAST_REPLY(const unsigned char *p HEIMDAL_UNUSED_ATTRIBUTE, size_t len HEIMDAL_UNUSED_ATTRIBUTE, PA_FX_FAST_REPLY *data, size_t *size)
{
size_t ret = 0;
size_t l HEIMDAL_UNUSED_ATTRIBUTE;
int e HEIMDAL_UNUSED_ATTRIBUTE;

memset(data, 0, sizeof(*data));
if (der_match_tag(p, len, ASN1_C_CONTEXT, CONS, 0, NULL) == 0) {
{
size_t armored_data_datalen, armored_data_oldlen;
Der_type armored_data_type;
e = der_match_tag_and_length(p, len, ASN1_C_CONTEXT, &armored_data_type, 0, &armored_data_datalen, &l);
if (e == 0 && armored_data_type != CONS) { e = ASN1_BAD_ID; }
if(e) goto fail;
p += l; len -= l; ret += l;
armored_data_oldlen = len;
if (armored_data_datalen > len) { e = ASN1_OVERRUN; goto fail; }
len = armored_data_datalen;
e = decode_KrbFastArmoredRep(p, len, &(data)->u.armored_data, &l);
if(e) goto fail;
p += l; len -= l; ret += l;
len = armored_data_oldlen - armored_data_datalen;
}
(data)->element = choice_PA_FX_FAST_REPLY_armored_data;
}
else {
(data)->u.asn1_ellipsis.data = calloc(1, len);
if ((data)->u.asn1_ellipsis.data == NULL) {
e = ENOMEM; goto fail;
}
(data)->u.asn1_ellipsis.length = len;
memcpy((data)->u.asn1_ellipsis.data, p, len);
(data)->element = choice_PA_FX_FAST_REPLY_asn1_ellipsis;
p += len;
ret += len;
len = 0;
}
if(size) *size = ret;
return 0;
fail:
free_PA_FX_FAST_REPLY(data);
return e;
}
