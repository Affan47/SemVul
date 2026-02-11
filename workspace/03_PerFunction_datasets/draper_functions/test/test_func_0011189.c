generic_callback(const char *tag, gpointer globaldata, gpointer data)
{
    GncExampleAccount *gea = (GncExampleAccount*)globaldata;

    if (g_strcmp0(tag, "gnc:account") == 0)
    {
        add_account_local(gea, (Account*)data);
    }
    return TRUE;
}
