decode_KeyUsage(const unsigned char *p HEIMDAL_UNUSED_ATTRIBUTE, size_t len HEIMDAL_UNUSED_ATTRIBUTE, KeyUsage *data, size_t *size)
{
size_t ret = 0;
size_t l HEIMDAL_UNUSED_ATTRIBUTE;
int e HEIMDAL_UNUSED_ATTRIBUTE;

memset(data, 0, sizeof(*data));
{
size_t Top_datalen, Top_oldlen;
Der_type Top_type;
e = der_match_tag_and_length(p, len, ASN1_C_UNIV, &Top_type, UT_BitString, &Top_datalen, &l);
if (e == 0 && Top_type != PRIM) { e = ASN1_BAD_ID; }
if(e) goto fail;
p += l; len -= l; ret += l;
Top_oldlen = len;
if (Top_datalen > len) { e = ASN1_OVERRUN; goto fail; }
len = Top_datalen;
if (len < 1) return ASN1_OVERRUN;
p++; len--; ret++;
do {
if (len < 1) break;
(data)->digitalSignature = (*p >> 7) & 1;
(data)->nonRepudiation = (*p >> 6) & 1;
(data)->keyEncipherment = (*p >> 5) & 1;
(data)->dataEncipherment = (*p >> 4) & 1;
(data)->keyAgreement = (*p >> 3) & 1;
(data)->keyCertSign = (*p >> 2) & 1;
(data)->cRLSign = (*p >> 1) & 1;
(data)->encipherOnly = (*p >> 0) & 1;
p++; len--; ret++;
if (len < 1) break;
(data)->decipherOnly = (*p >> 7) & 1;
} while(0);
p += len; ret += len;
len = Top_oldlen - Top_datalen;
}
if(size) *size = ret;
return 0;
fail:
free_KeyUsage(data);
return e;
}
