newRec(record * curr)
{
    record *newr;

    newr = (record *) malloc(sizeof(record));
    if (!newr) {
	fprintf(stderr, "mkdefs: out of memory, line %d\n", lineno);
	exit(1);
    }
    curr->next = newr;
    newr->next = 0;
    return newr;
}
