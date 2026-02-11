new_couple(const char* k,void *d)
{
struct couple_t *tmp = malloc(sizeof(struct couple_t));
MALLOC_CHECK(tmp);

tmp->data = d;
tmp->key=strdup(k);
MALLOC_CHECK(tmp->key);

return tmp;
}
