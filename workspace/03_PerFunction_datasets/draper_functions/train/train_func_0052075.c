fetion_account_update_portrait(fetion_account *ac)
{
    portrait_data *data;
    const gchar   *checksum;

    g_return_val_if_fail(ac != NULL, HYBRID_ERROR);

    data                = g_new0(portrait_data, 1);
    data->ac            = ac;
    data->portrait_type = PORTRAIT_TYPE_ACCOUNT;

    checksum = hybrid_account_get_checksum(ac->account);

    if (checksum != NULL && g_strcmp0(checksum, ac->portrait_crc) == 0) {
        return HYBRID_OK;
    }

    hybrid_proxy_connect(ac->portrait_host_name, 80, portrait_conn_cb, data);

    return HYBRID_OK;
}
