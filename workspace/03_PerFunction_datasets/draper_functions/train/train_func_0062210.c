agnodeattr_delete(Agnode_t * n)
{
    Agattr_t *rec;

    if ((rec = agattrrec(n))) {
	freeattr((Agobj_t *) n, rec);
	agdelrec(n, AgDataRecName);
    }
}
