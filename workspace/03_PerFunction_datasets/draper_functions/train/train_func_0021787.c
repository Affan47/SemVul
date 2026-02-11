SECU_displayVerifyLog(FILE *outfile, CERTVerifyLog *log,
                      PRBool verbose)
{
    CERTVerifyLogNode *node   = NULL;
    unsigned int       depth  = (unsigned int)-1;
    unsigned int       flags  = 0;
    char *             errstr = NULL;

    if (log->count > 0) {
	fprintf(outfile,"PROBLEM WITH THE CERT CHAIN:\n");
	for (node = log->head; node; node = node->next) {
	    if (depth != node->depth) {
		depth = node->depth;
		fprintf(outfile,"CERT %d. %s %s:\n", depth,
				 bestCertName(node->cert),
			  	 depth ? "[Certificate Authority]": "");
	    	if (verbose) {
		    const char * emailAddr;
		    emailAddr = CERT_GetFirstEmailAddress(node->cert);
		    if (emailAddr) {
		    	fprintf(outfile,"Email Address(es): ");
			do {
			    fprintf(outfile, "%s\n", emailAddr);
			    emailAddr = CERT_GetNextEmailAddress(node->cert,
			                                         emailAddr);
			} while (emailAddr);
		    }
		}
	    }
	    fprintf(outfile, "  ERROR %ld: %s\n", node->error,
			    SECU_Strerror(node->error));
	    errstr = NULL;
	    switch (node->error) {
	    case SEC_ERROR_INADEQUATE_KEY_USAGE:
		flags = (unsigned int)node->arg;
		switch (flags) {
		case KU_DIGITAL_SIGNATURE:
		    errstr = "Cert cannot sign.";
		    break;
		case KU_KEY_ENCIPHERMENT:
		    errstr = "Cert cannot encrypt.";
		    break;
		case KU_KEY_CERT_SIGN:
		    errstr = "Cert cannot sign other certs.";
		    break;
		default:
		    errstr = "[unknown usage].";
		    break;
		}
	    case SEC_ERROR_INADEQUATE_CERT_TYPE:
		flags = (unsigned int)node->arg;
		switch (flags) {
		case NS_CERT_TYPE_SSL_CLIENT:
		case NS_CERT_TYPE_SSL_SERVER:
		    errstr = "Cert cannot be used for SSL.";
		    break;
		case NS_CERT_TYPE_SSL_CA:
		    errstr = "Cert cannot be used as an SSL CA.";
		    break;
		case NS_CERT_TYPE_EMAIL:
		    errstr = "Cert cannot be used for SMIME.";
		    break;
		case NS_CERT_TYPE_EMAIL_CA:
		    errstr = "Cert cannot be used as an SMIME CA.";
		    break;
		case NS_CERT_TYPE_OBJECT_SIGNING:
		    errstr = "Cert cannot be used for object signing.";
		    break;
		case NS_CERT_TYPE_OBJECT_SIGNING_CA:
		    errstr = "Cert cannot be used as an object signing CA.";
		    break;
		default:
		    errstr = "[unknown usage].";
		    break;
		}
	    case SEC_ERROR_UNKNOWN_ISSUER:
	    case SEC_ERROR_UNTRUSTED_ISSUER:
	    case SEC_ERROR_EXPIRED_ISSUER_CERTIFICATE:
		errstr = node->cert->issuerName;
		break;
	    default:
		break;
	    }
	    if (errstr) {
		fprintf(stderr,"    %s\n",errstr);
	    }
	}
    }
}
