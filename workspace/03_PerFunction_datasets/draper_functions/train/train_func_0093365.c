gva_get_soup_session (void)
{
        static SoupSession *soup_session = NULL;

        if (G_UNLIKELY (soup_session == NULL))
        {
                soup_session = soup_session_async_new ();

                soup_session_add_feature_by_type (
                        soup_session, SOUP_TYPE_CACHE);

                if (gva_get_debug_flags () & GVA_DEBUG_HTTP)
                        soup_session_add_feature_by_type (
                                soup_session, SOUP_TYPE_LOGGER);


                g_object_set (
                        soup_session,
                        SOUP_SESSION_USER_AGENT,
                        "Mozilla/5.0", NULL);
        }

        return soup_session;
}
