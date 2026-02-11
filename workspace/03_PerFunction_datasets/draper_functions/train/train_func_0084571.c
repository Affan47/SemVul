prettyPrintTag(FILE *out, const unsigned char *src, const unsigned char *end,
	       unsigned char *codep, unsigned int level, PRBool raw)
{
    int rv;
    unsigned char code, tagnum;

    if (src >= end) {
	PORT_SetError(SEC_ERROR_BAD_DER);
	return -1;
    }

    code = *src;
    tagnum = code & SEC_ASN1_TAGNUM_MASK;


    if (tagnum == SEC_ASN1_HIGH_TAG_NUMBER) {
        PORT_SetError(SEC_ERROR_BAD_DER);
	return -1;
    }

    if (raw)
	rv = prettyPrintByte(out, code, level);
    else
	rv = prettyIndent(out, level);

    if (rv < 0)
	return rv;

    if (code & SEC_ASN1_CONSTRUCTED) {
        rv = fprintf(out, "C-");
	if (rv < 0) {
	    PORT_SetError(SEC_ERROR_IO);
	    return rv;
	}
    }

    switch (code & SEC_ASN1_CLASS_MASK) {
    case SEC_ASN1_UNIVERSAL:
        rv = fprintf(out, "%s ", prettyTagType[tagnum]);
	break;
    case SEC_ASN1_APPLICATION:
        rv = fprintf(out, "Application: %d ", tagnum);
	break;
    case SEC_ASN1_CONTEXT_SPECIFIC:
        rv = fprintf(out, "[%d] ", tagnum);
	break;
    case SEC_ASN1_PRIVATE:
        rv = fprintf(out, "Private: %d ", tagnum);
	break;
    }

    if (rv < 0) {
        PORT_SetError(SEC_ERROR_IO);
	return rv;
    }

    *codep = code;

    return 1;
}
