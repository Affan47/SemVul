_local_gsyncd_start (dict_t *this, char *key, data_t *value, void *data)
{
        char                        *slave = NULL;
        int                          uuid_len = 0;
        char                         uuid_str[64] = {0};
        glusterd_volinfo_t           *volinfo = NULL;

        volinfo = data;
        GF_ASSERT (volinfo);
        slave = strchr(value->data, ':');
        if (slave)
                slave ++;
        else
                return;
        uuid_len = (slave - value->data - 1);


        strncpy (uuid_str, (char*)value->data, uuid_len);
        glusterd_start_gsync (volinfo, slave, uuid_str, NULL);
}
