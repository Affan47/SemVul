mailcap_lookup(char *type, char *subtype)
{
    MailcapEntry	*loop;

    for (loop = mailcaps[hash(type)] ; loop ; loop = loop->next)
	if (strcmp(type, loop->type) == 0 &&
	    (!loop->subtype || strcmp(subtype, loop->subtype) == 0))
	    return &loop->data;

    return NULL;
}
