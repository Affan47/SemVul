get(void)
{
    struct cost *p;

    if (first_free == NULL) {
	allocate();
    }

    p = first_free;
    first_free = p->lower;
    if (first_free->lower == NULL) {
	allocate();
    }
    return p;
}
