gupnp_dlna_profile_guesser_class_init
                                   (GUPnPDLNAProfileGuesserClass *guesser_class)
{
        GObjectClass *object_class = G_OBJECT_CLASS (guesser_class);
        GParamSpec *pspec;
        guint iter;

        object_class->get_property = gupnp_dlna_profile_guesser_get_property;
        object_class->set_property = gupnp_dlna_profile_guesser_set_property;


        pspec = g_param_spec_boolean ("relaxed-mode",
                                      "Relaxed mode property",
                                      "Indicates that profile matching should"
                                      "be strictly compliant with the DLNA "
                                      "specification",
                                      FALSE,
                                      G_PARAM_READWRITE |
                                      G_PARAM_CONSTRUCT_ONLY);
        g_object_class_install_property (object_class,
                                         PROP_DLNA_RELAXED_MODE,
                                         pspec);


        pspec = g_param_spec_boolean ("extended-mode",
                                      "Extended mode property",
                                      "Indicates support for profiles that are "
                                      "not part of the DLNA specification",
                                      FALSE,
                                      G_PARAM_READWRITE |
                                      G_PARAM_CONSTRUCT_ONLY);
        g_object_class_install_property (object_class,
                                         PROP_DLNA_EXTENDED_MODE,
                                         pspec);


        signals[DONE] =
                g_signal_new ("done",
                              G_TYPE_FROM_CLASS (guesser_class),
                              G_SIGNAL_RUN_LAST,
                              0,
                              NULL,
                              NULL,
                              g_cclosure_marshal_generic,
                              G_TYPE_NONE,
                              3,
                              GUPNP_TYPE_DLNA_INFORMATION,
                              GUPNP_TYPE_DLNA_PROFILE,
                              G_TYPE_ERROR);


        for (iter = 0; iter < 4; ++iter) {
                gboolean relaxed = (iter > 1);
                gboolean extended = ((iter) % 2 != 0);
                guint rel_index = (relaxed ? 1 : 0);
                guint ext_index = (extended ? 1 : 0);
                GUPnPDLNAProfileLoader *loader = gupnp_dlna_profile_loader_new
                                        (relaxed,
                                         extended);

                profiles_list[rel_index][ext_index] =
                               gupnp_dlna_profile_loader_get_from_disk (loader);
                g_object_unref (loader);
        }

        g_type_class_add_private (guesser_class,
                                  sizeof (GUPnPDLNAProfileGuesserPrivate));
}
