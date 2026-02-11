amber_paf_set_type(AmPaf *self, const cxchar *type)
{

    cx_assert(self != NULL);

    if (type == NULL) {
        return -1;
    }

    if (self->header->type != NULL) {
        self->header->type = cx_realloc(self->header->type,
                                        (strlen(type) + 1) * sizeof(cxchar));
        strcpy(self->header->type, type);
    }
    else {
        self->header->type = cx_strdup(type);
    }

    return 0;

}
