xml_parse_browse_artist(struct artist_browse* a,
                             unsigned char* xml,
                             int len,
                             bool high_bitrate)
{
    ezxml_t top = ezxml_parse_str(xml, len);

    xmlstrncpy(a->name, sizeof a->name, top, "name", -1);
    xmlstrncpy(a->genres, sizeof a->genres, top, "genres", -1);
    xmlstrncpy(a->years_active, sizeof a->years_active, top, "years-active",-1);
    xmlstrncpy(a->id, sizeof a->id, top, "id", -1);
    xmlstrncpy(a->portrait_id, sizeof a->portrait_id, top,
               "portrait", 0, "id", -1);
    xmlatof(&a->popularity, top, "popularity", -1);

    ezxml_t x = ezxml_get(top, "bios",0,"bio",0,"text",-1);
    if (x) {
        int len = strlen(x->txt);
        a->text = malloc(len + 1);
        memcpy(a->text, x->txt, len+1);
    }


    x = ezxml_get(top, "albums",-1);
    struct album_browse* prev = NULL;
    struct album_browse* album = calloc(1, sizeof(struct album_browse));
    a->albums = album;
    int album_count = 0;
    for (ezxml_t xalb = ezxml_get(x, "album", -1); xalb; xalb = xalb->next) {
        if (prev) {
            album = calloc(1, sizeof(struct album));
            prev->next = album;
        }

        parse_browse_album(xalb, album, high_bitrate);

        prev = album;
        album_count++;
    }
    a->num_albums = album_count;
    ezxml_free(top);

    return true;
}
