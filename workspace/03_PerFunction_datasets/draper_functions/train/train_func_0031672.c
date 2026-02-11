info_set_from_container_information (GUPnPDLNAContainerInformation *info)
{
        static const gchar *const type = "container";
        GUPnPDLNAInfoSet *info_set = create_info_set
                              (gupnp_dlna_container_information_get_mime (info),
                               "Container");

        if (info_set == NULL)
                return NULL;

        add_int (info_set,
                 "mpegversion",
                 gupnp_dlna_container_information_get_mpeg_version (info),
                 type);

        add_int (info_set,
                 "packetsize",
                 gupnp_dlna_container_information_get_packet_size (info),
                 type);

        add_string (info_set,
                    "profile",
                    gupnp_dlna_container_information_get_profile (info),
                    type);

        add_bool (info_set,
                  "systemstream",
                  gupnp_dlna_container_information_is_system_stream (info),
                  type);

        add_string (info_set,
                    "variant",
                    gupnp_dlna_container_information_get_variant (info),
                    type);

        return info_set;
}
