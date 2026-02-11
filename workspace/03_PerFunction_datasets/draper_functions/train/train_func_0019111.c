save_data(Eet_File *ef, Eina_Array *data, const char *key)
{
    Efreet_Cache_Array_String *save;
    unsigned int i;

    if (!data || !data->count) return;

    save = NEW(Efreet_Cache_Array_String, 1);
    save->array = NEW(char *, data->count);
    save->array_count = 0;
    for (i = 0; i < data->count; ++i)
        save->array[save->array_count++] = data->data[i];
    eet_data_write(ef, efreet_array_string_edd(), key, save, 1);
    IF_FREE(save->array);
    free(save);
}
