grow_build_string(Clp_BuildString *bs, int want)
{
    char *new_text;
    int ipos = bs->pos - bs->text;
    int new_capacity = bs->capacity;
    while (want >= new_capacity)
	new_capacity *= 2;
    new_text = (char *)realloc(bs->text, new_capacity);
    if (!new_text) {
	bs->bad = 1;
	return 0;
    } else {
	bs->text = new_text;
	bs->pos = bs->text + ipos;
	bs->capacity = new_capacity;
	return 1;
    }
}
