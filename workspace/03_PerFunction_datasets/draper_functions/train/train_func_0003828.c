_get_status_mst_slv (dict_t *this, char *key, data_t *value, void *data)
{
        glusterd_gsync_status_temp_t  *param = NULL;
        char                          *slave = NULL;
        int                           ret = 0;

        param = (glusterd_gsync_status_temp_t *)data;

        GF_ASSERT (param);
        GF_ASSERT (param->volinfo);

        slave = strchr(value->data, ':');
        if (slave)
                slave ++;
        else
                return;

        ret = glusterd_get_gsync_status_mst_slv(param->volinfo,
                                                slave, param->rsp_dict);

}
