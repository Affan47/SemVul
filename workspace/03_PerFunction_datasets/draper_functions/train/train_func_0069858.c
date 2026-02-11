nssCertificateArray_Traverse (
  NSSCertificate **certs,
  PRStatus (* callback)(NSSCertificate *c, void *arg),
  void *arg
)
{
    PRStatus status = PR_SUCCESS;
    if (certs) {
	NSSCertificate **certp;
	for (certp = certs; *certp; certp++) {
	    status = (*callback)(*certp, arg);
	    if (status != PR_SUCCESS) {
		break;
	    }
	}
    }
    return status;
}
