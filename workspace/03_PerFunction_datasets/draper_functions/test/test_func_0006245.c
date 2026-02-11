variantsortf(var_rec *a, var_rec *b) {


    if (a->source_quality < b->source_quality)
        return 1;
    if (a->source_quality > b->source_quality)
        return -1;


    return strcmp(a->file_name, b->file_name);
}
