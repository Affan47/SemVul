zmat_entries_get(gpointer data)
{
struct zmat_pak *zmat = data;

g_assert(zmat != NULL);

return(g_slist_length(zmat->zlines));
}
