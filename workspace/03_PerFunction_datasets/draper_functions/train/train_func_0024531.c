ario_audioscrobbler_is_queueable (ArioServerSong *song)
{
        ARIO_LOG_FUNCTION_START
        const char *title;
        const char *artist;
        gulong duration;


        title = song->title;
        artist = song->artist;
        duration = song->time;


        if (duration < 30) {
                ARIO_LOG_INFO ("entry not queueable: shorter than 30 seconds");
                return FALSE;
        }
        if (!artist) {
                ARIO_LOG_INFO ("entry not queueable: artist is unknown");
                return FALSE;
        }
        if (!title) {
                ARIO_LOG_INFO ("entry not queueable: title is unknown");
                return FALSE;
        }

        ARIO_LOG_DBG ("entry is queueable");
        return TRUE;
}
