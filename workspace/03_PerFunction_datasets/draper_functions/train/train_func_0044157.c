lightdm_greeter_get_hint (LightDMGreeter *greeter, const gchar *name)
{
    g_return_val_if_fail (LIGHTDM_IS_GREETER (greeter), NULL);
    return g_hash_table_lookup (GET_PRIVATE (greeter)->hints, name);
}
