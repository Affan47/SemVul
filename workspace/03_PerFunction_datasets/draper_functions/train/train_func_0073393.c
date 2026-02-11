decode_KrbFastArmoredRep(const unsigned char *p HEIMDAL_UNUSED_ATTRIBUTE, size_t len HEIMDAL_UNUSED_ATTRIBUTE, KrbFastArmoredRep *data, size_t *size)
{
size_t ret = 0;
size_t l HEIMDAL_UNUSED_ATTRIBUTE;
int e HEIMDAL_UNUSED_ATTRIBUTE;

memset(data, 0, sizeof(*data));
{
size_t Top_datalen, Top_oldlen;
Der_type Top_type;
e = der_match_tag_and_length(p, len, ASN1_C_UNIV, &Top_type, UT_Sequence, &Top_datalen, &l);
if (e == 0 && Top_type != CONS) { e = ASN1_BAD_ID; }
if(e) goto fail;
p += l; len -= l; ret += l;
Top_oldlen = len;
if (Top_datalen > len) { e = ASN1_OVERRUN; goto fail; }
len = Top_datalen;
{
size_t enc_fast_rep_datalen, enc_fast_rep_oldlen;
Der_type enc_fast_rep_type;
e = der_match_tag_and_length(p, len, ASN1_C_CONTEXT, &enc_fast_rep_type, 0, &enc_fast_rep_datalen, &l);
if (e == 0 && enc_fast_rep_type != CONS) { e = ASN1_BAD_ID; }
if(e) goto fail;
p += l; len -= l; ret += l;
enc_fast_rep_oldlen = len;
if (enc_fast_rep_datalen > len) { e = ASN1_OVERRUN; goto fail; }
len = enc_fast_rep_datalen;
e = decode_EncryptedData(p, len, &(data)->enc_fast_rep, &l);
if(e) goto fail;
p += l; len -= l; ret += l;
len = enc_fast_rep_oldlen - enc_fast_rep_datalen;
}
len = Top_oldlen - Top_datalen;
}
if(size) *size = ret;
return 0;
fail:
free_KrbFastArmoredRep(data);
return e;
}
