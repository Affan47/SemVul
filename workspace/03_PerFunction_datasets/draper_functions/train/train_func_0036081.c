parse_db(const char *name, uint8_t *data, uint32_t len, int sig, int entry)
{
	EFI_SIGNATURE_LIST  *CertList = (EFI_SIGNATURE_LIST *)data;
	EFI_SIGNATURE_DATA  *Cert;
	long count = 0, DataSize = len;
	int size;

	certlist_for_each_certentry(CertList, data, size, DataSize) {
		int Index = 0;
		const char *ext;

		if (sig != -1 && count != sig)
			continue;


		if (compare_guid(&CertList->SignatureType, &X509_GUID)== 0) {
			ext = "X509";
		} else if (compare_guid(&CertList->SignatureType, &RSA2048_GUID) == 0) {
			ext = "RSA2048";
		} else if (compare_guid(&CertList->SignatureType, &PKCS7_GUID) == 0) {
			ext = "PKCS7";
		} else if (compare_guid(&CertList->SignatureType, &EFI_CERT_SHA256_GUID) == 0) {
			ext = "SHA256";
		} else {
			ext = "Unknown";
		}

		printf("%s: List %ld, type %s\n", name, count++, ext);

		certentry_for_each_cert(Cert, CertList) {
			if (entry != -1 && Index != entry)
				continue;

			printf("    Signature %d, size %d, owner %s\n",
			      Index++, CertList->SignatureSize,
			      guid_to_str(&Cert->SignatureOwner));

			if (strcmp(ext, "X509") == 0) {
				const unsigned char *buf = (unsigned char *)Cert->SignatureData;
				X509 *X = d2i_X509(NULL, &buf,
						   CertList->SignatureSize);
				X509_NAME *issuer = X509_get_issuer_name(X);
				X509_NAME *subject = X509_get_subject_name(X);

				printf("        Subject:\n");
				X509_NAME_print_ex_fp(stdout, subject, 12, XN_FLAG_SEP_CPLUS_SPC);
				printf("\n        Issuer:\n");
				X509_NAME_print_ex_fp(stdout, issuer, 12, XN_FLAG_SEP_CPLUS_SPC);
				printf("\n");

			} else if (strcmp(ext, "SHA256") == 0) {
				uint8_t *hash = Cert->SignatureData;
				int j;

				printf("        Hash:");
				for (j = 0; j < SHA256_DIGEST_SIZE; j++) {
					printf("%02x", hash[j]);
				}
				printf("\n");
			}
		}
	}
}
