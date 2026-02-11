glusterd_uuid_init ()
{
        int             ret = -1;
        xlator_t        *this = NULL;
        glusterd_conf_t *priv = NULL;

        this = THIS;
        GF_ASSERT (this);
        priv = this->private;

	ret = glusterd_retrieve_uuid ();
	if (ret == 0) {
		gf_log (this->name, GF_LOG_INFO,
			"retrieved UUID: %s", uuid_utoa (priv->uuid));
		return 0;
	}

        ret = glusterd_uuid_generate_save ();

        if (ret) {
                gf_log ("glusterd", GF_LOG_ERROR,
                          "Unable to generate and save new UUID");
                return ret;
        }

        return 0;
}
