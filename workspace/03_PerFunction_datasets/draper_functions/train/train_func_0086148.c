removeHeader(HTTPHeader *header, char *fName)
{
	HTTPHeader *auxHeader = NULL;

	auxHeader = header;
	while (auxHeader && strcmp(auxHeader->fName, fName) != 0)
		auxHeader = auxHeader->next;

	if (auxHeader != NULL) {
		if (auxHeader->prev == NULL) {
			header = auxHeader->next;
			header->prev = NULL;
		} else {
			if (auxHeader->next)
				auxHeader->next->prev = auxHeader->prev;
			if (auxHeader->prev)
				auxHeader->prev->next = auxHeader->next;
		}
		free(auxHeader->fName);
		free(auxHeader->fValue);
		free(auxHeader);
	}

	return header;
}
