marker_getxattr_stampfile_cbk (call_frame_t *frame, xlator_t *this,
                               const char *name, struct volume_mark *vol_mark)
{
        int32_t   ret  = -1;
        dict_t   *dict = NULL;

        if (vol_mark == NULL){
                STACK_UNWIND_STRICT (getxattr, frame, -1, ENOMEM, NULL);

                goto out;
        }

        dict = dict_new ();

        ret = dict_set_bin (dict, (char *)name, vol_mark,
                            sizeof (struct volume_mark));
        if (ret)
                gf_log (this->name, GF_LOG_WARNING, "failed to set key %s",
                        name);

        STACK_UNWIND_STRICT (getxattr, frame, 0, 0, dict);

        dict_unref (dict);
out:
        return 0;
}
