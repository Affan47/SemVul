PK11_NumberCertsForCertSubject(CERTCertificate *cert)
{
    CK_OBJECT_CLASS certClass = CKO_CERTIFICATE;
    CK_ATTRIBUTE theTemplate[] = {
	{ CKA_CLASS, NULL, 0 },
	{ CKA_SUBJECT, NULL, 0 },
    };
    CK_ATTRIBUTE *attr = theTemplate;
   int templateSize = sizeof(theTemplate)/sizeof(theTemplate[0]);

    PK11_SETATTRS(attr,CKA_CLASS, &certClass, sizeof(certClass)); attr++;
    PK11_SETATTRS(attr,CKA_SUBJECT,cert->derSubject.data,cert->derSubject.len);

    if (cert->slot == NULL) {
	PK11SlotList *list = PK11_GetAllTokens(CKM_INVALID_MECHANISM,
							PR_FALSE,PR_TRUE,NULL);
	PK11SlotListElement *le;
	int count = 0;

	if (!list) {

            return 0;
	}


	for (le = list->head; le; le = le->next) {
	    count += PK11_NumberObjectsFor(le->slot,theTemplate,templateSize);
	}
	PK11_FreeSlotList(list);
	return count;
    }

    return PK11_NumberObjectsFor(cert->slot,theTemplate,templateSize);
}
