afr_sh_entry_impunge_mkdir (call_frame_t *impunge_frame, xlator_t *this,
                            int child_index, struct iatt *stbuf)
{
        afr_private_t   *priv = NULL;
        afr_local_t     *impunge_local = NULL;
        dict_t          *dict = NULL;

        int ret = 0;

        priv = this->private;
        impunge_local = impunge_frame->local;

        dict = dict_new ();
        if (!dict) {
                gf_log (this->name, GF_LOG_ERROR,
                        "Out of memory");
                return 0;
        }

        GF_ASSERT (!uuid_is_null (stbuf->ia_gfid));
        ret = afr_set_dict_gfid (dict, stbuf->ia_gfid);
        if (ret)
                gf_log (this->name, GF_LOG_INFO, "%s: gfid set failed",
                        impunge_local->loc.path);

        gf_log (this->name, GF_LOG_DEBUG,
                "creating missing directory %s on %s",
                impunge_local->loc.path,
                priv->children[child_index]->name);

        STACK_WIND_COOKIE (impunge_frame, afr_sh_entry_impunge_newfile_cbk,
                           (void *) (long) child_index,
                           priv->children[child_index],
                           priv->children[child_index]->fops->mkdir,
                           &impunge_local->loc,
                           st_mode_from_ia (stbuf->ia_prot, stbuf->ia_type),
                           dict);

        if (dict)
                dict_unref (dict);

        return 0;
}
