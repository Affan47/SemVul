initsymtab(void)
{
    unsigned int i, j;
    struct keystruct *p;

    for (i = 1; i < KEYWORDS; ++i) {
	p = keyword + i;
	j = hash(p->text) % HASHMOD;
	p->next = hashtab[j];
	hashtab[j] = p;
    }
}
