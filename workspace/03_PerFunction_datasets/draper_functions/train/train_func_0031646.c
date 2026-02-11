do_yp_add (ypdata_t *yp, char *s, unsigned len)
{
    int ret;
    char *value;

    value = stats_get_value (yp->mount, "server_type");
    add_yp_info (yp, value, YP_SERVER_TYPE);
    free (value);

    value = stats_get_value (yp->mount, "server_name");
    add_yp_info (yp, value, YP_SERVER_NAME);
    free (value);

    value = stats_get_value (yp->mount, "server_url");
    add_yp_info (yp, value, YP_SERVER_URL);
    free (value);

    value = stats_get_value (yp->mount, "genre");
    add_yp_info (yp, value, YP_SERVER_GENRE);
    free (value);

    value = stats_get_value (yp->mount, "bitrate");
    if (value == NULL)
        value = stats_get_value (yp->mount, "ice-bitrate");
    add_yp_info (yp, value, YP_BITRATE);
    free (value);

    value = stats_get_value (yp->mount, "server_description");
    add_yp_info (yp, value, YP_SERVER_DESC);
    free (value);

    value = stats_get_value (yp->mount, "subtype");
    add_yp_info (yp, value, YP_SUBTYPE);
    free (value);

    value = stats_get_value (yp->mount, "audio_info");
    add_yp_info (yp, value, YP_AUDIO_INFO);
    free (value);

    ret = snprintf (s, len, "action=add&sn=%s&genre=%s&cpswd=%s&desc="
                    "%s&url=%s&listenurl=%s&type=%s&stype=%s&b=%s&%s\r\n",
                    yp->server_name, yp->server_genre, yp->cluster_password,
                    yp->server_desc, yp->url, yp->listen_url,
                    yp->server_type, yp->subtype, yp->bitrate, yp->audio_info);
    if (ret >= (signed)len)
        return ret+1;
    ret = send_to_yp ("add", yp, s);
    if (ret == 0)
    {
        yp->process = do_yp_touch;

        yp->next_update = time(NULL) + 5;
    }
    return ret;
}
