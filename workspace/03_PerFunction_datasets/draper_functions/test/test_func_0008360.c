SEC_PKCS12ValidData(char *buf, int bufLen, long int totalLength)
{
    int lengthLength;

    PRBool valid = PR_FALSE;

    if(buf == NULL) {
	return PR_FALSE;
    }


    if(*buf == (SEC_ASN1_CONSTRUCTED | SEC_ASN1_SEQUENCE)) {
	totalLength--;
	buf++;

	lengthLength = (long int)SEC_ASN1LengthLength(totalLength - 1);
	if(totalLength > 0x7f) {
	    lengthLength--;
	    *buf &= 0x7f;
	    if((*buf - (char)lengthLength) == 0) {
		valid = PR_TRUE;
	    }
	} else {
	    lengthLength--;
	    if((*buf - (char)lengthLength) == 0) {
		valid = PR_TRUE;
	    }
	}
    }

    return valid;
}
