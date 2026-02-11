ber_check_memory(mem_chunk_t **curr, unsigned int needed) {
    mem_chunk_t *new;
    if ((*curr)->curr-needed >= (*curr)->top)
	return ASN1_OK;

    if ((new = ber_new_chunk((*curr)->length > needed ? (*curr)->length * 2 : (*curr)->length + needed)) == NULL)
	return ASN1_ERROR;
    new->next = *curr;
    *curr = new;
    return ASN1_OK;
}
