glusterfs_this_init ()
{
        int  ret = 0;

        ret = pthread_key_create (&this_xlator_key, glusterfs_this_destroy);
        if (ret != 0) {
                gf_log ("", GF_LOG_WARNING, "failed to create the pthread key");
                return ret;
        }

        global_xlator.name = "glusterfs";
        global_xlator.type = "global";

        INIT_LIST_HEAD (&global_xlator.volume_options);

        return ret;
}
