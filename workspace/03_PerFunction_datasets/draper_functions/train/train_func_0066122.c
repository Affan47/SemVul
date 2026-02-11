get_method(address_family * af, char *name)
{
    int i;
    for (i = 0; i < af->n_methods; i++) {
        if (strcmp(af->method[i].name, name) == 0) {
            return &af->method[i];
        }
    }
    return NULL;
}
