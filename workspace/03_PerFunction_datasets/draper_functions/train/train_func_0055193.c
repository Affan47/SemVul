sam_header_free(void *_header)
{
	HeaderDict *header = (HeaderDict*)_header;
    list_t *hlines = header;
    while (hlines)
    {
        sam_header_line_free(hlines->data);
        hlines = hlines->next;
    }
    list_free(header);
}
