rl_free(gpointer key, gpointer value, gpointer user_data)
{
    if (value != NULL_PROXY && value != BNODE_PROXY) {
        free(value);
    }
}
