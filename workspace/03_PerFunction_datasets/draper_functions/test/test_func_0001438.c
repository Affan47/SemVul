rmXMLAtt (XMLEle *ep, const char *name)
{
	int i;

	for (i = 0; i < ep->nat; i++) {
	    if (strcmp (ep->at[i]->name.s, name) == 0) {
		freeAtt (ep->at[i]);
		memmove (&ep->at[i],&ep->at[i+1],(--ep->nat-i)*sizeof(XMLAtt*));
		return;
	    }
	}
}
