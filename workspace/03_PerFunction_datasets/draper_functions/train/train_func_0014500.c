message_parse(const char *fname, struct index_record *record)
{
    struct body *body = NULL;
    FILE *f;
    int r;

    f = fopen(fname, "r");
    if (!f) return IMAP_IOERROR;

    r = message_parse_file(f, NULL, NULL, &body);
    if (!r) r = message_create_record(record, body);

    if (f) fclose(f);

    if (body) {
	message_free_body(body);
	free(body);
    }

    return r;
}
