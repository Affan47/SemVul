scamp_catalog_open_for_writing(const char* filename, anbool ref) {
    scamp_cat_t* scamp;
    scamp = calloc(1, sizeof(scamp_cat_t));
    scamp->table = fitstable_open_for_writing(filename);
    if (!scamp->table) {
        ERROR("Failed to open scamp catalog for writing");
        free(scamp);
        return NULL;
    }
    scamp->ref = ref;
    return scamp;
}
