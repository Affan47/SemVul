smf_metatext(type,leng,mess)
char *mess;
{
        static char *ttype[] = {
                NULL,
                "Text Event",
                "Copyright Notice",
                "Sequence/Track Name",
                "Instrument Name",
                "Lyric",
                "Marker",
                "Cue Point",
                "Unrecognized"
        };
        int unrecognized = (sizeof(ttype)/sizeof(char *)) - 1;

        if ( type < 1 || type > unrecognized )
                type = unrecognized;
}
