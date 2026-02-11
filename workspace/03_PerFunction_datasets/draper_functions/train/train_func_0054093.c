GetMIMEDescription()
{
    gchar MimeTypes[4000];
    GmPrefStore *store;
    gboolean real_disabled = FALSE;

    g_type_init();
    store = gm_pref_store_new("gecko-mediaplayer");
    if (store != NULL) {
        real_disabled = gm_pref_store_get_boolean(store, DISABLE_REAL);
        gm_pref_store_free(store);
    }


    if (real_disabled) {
        return NULL;
    } else {

        g_strlcpy(MimeTypes,
                  "audio/x-pn-realaudio:ram,rm:RealAudio;"
                  "application/vnd.rn-realmedia:rm:RealMedia;"
                  "application/vnd.rn-realaudio:ra,ram:RealAudio;"
                  "video/vnd.rn-realvideo:rv:RealVideo;"
                  "audio/x-realaudio:ra:RealAudio;"
                  "audio/x-pn-realaudio-plugin:rpm:RealAudio;"
                  "application/smil:smil:SMIL;", sizeof(MimeTypes));

        return g_strdup(MimeTypes);
    }
}
