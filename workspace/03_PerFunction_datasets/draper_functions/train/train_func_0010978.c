on_unload(ErlNifEnv* env, void* priv_data)
{
    if (collators != NULL) {
        int i;

        for (i = 0; i < numCollators; i++) {
            ucol_close(collators[i]);
        }

        enif_free(collators);
    }

    if (collMutex != NULL) {
        enif_mutex_destroy(collMutex);
    }
}
