df_destroy(DocField *df)
{
    if (df->destroy_data) {
        int i;
        for (i = 0; i < df->size; i++) {
            free(df->data[i]);
        }
    }
    free(df->data);
    free(df->lengths);
    free(df->name);
    free(df);
}
