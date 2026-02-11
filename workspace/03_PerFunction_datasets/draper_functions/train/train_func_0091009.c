rb_do_operation_start (glusterd_volinfo_t *volinfo,
                       glusterd_brickinfo_t *src_brickinfo,
                       glusterd_brickinfo_t *dst_brickinfo)
{
        char start_value[8192] = {0,};
        int ret = -1;


        gf_log ("", GF_LOG_DEBUG,
                "replace-brick sending start xattr");

        ret = rb_spawn_maintenance_client (volinfo, src_brickinfo);
        if (ret) {
                gf_log ("", GF_LOG_DEBUG,
                        "Could not spawn maintenance "
                        "client");
                goto out;
        }

	gf_log ("", GF_LOG_DEBUG,
		"mounted the replace brick client");

        snprintf (start_value, 8192, "%s:%s:%d",
                  dst_brickinfo->hostname,
                  dst_brickinfo->path,
                  dst_brickinfo->port);


        ret = rb_send_xattr_command (volinfo, src_brickinfo,
                                     dst_brickinfo, RB_PUMP_START_CMD,
                                     start_value);
        if (ret) {
                gf_log ("", GF_LOG_DEBUG,
                        "Failed to send command to pump");
        }

        ret = rb_destroy_maintenance_client (volinfo, src_brickinfo);
        if (ret) {
                gf_log ("", GF_LOG_DEBUG,
                        "Failed to destroy maintenance "
                        "client");
                goto out;
        }

        gf_log ("", GF_LOG_DEBUG,
		"unmounted the replace brick client");
        ret = 0;

out:
        return ret;
}
