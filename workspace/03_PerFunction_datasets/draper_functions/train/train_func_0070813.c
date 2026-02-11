zmat_free(gpointer data)
{
struct zmat_pak *zmat = data;

g_assert(zmat != NULL);

g_free(zmat->distance_units);
g_free(zmat->angle_units);

free_slist(zmat->zlines);

g_slist_free(zmat->zcores);
g_hash_table_destroy(zmat->vars);
g_hash_table_destroy(zmat->consts);
g_free(zmat);
}
