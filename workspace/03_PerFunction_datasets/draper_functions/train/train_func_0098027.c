mp3tunes_locker_playlists(mp3tunes_locker_object_t *obj, mp3tunes_locker_playlist_list_t **playlists) {
    xml_xpath_t* xml_xpath;
    xmlXPathObjectPtr xpath_obj;
    xmlNodeSetPtr nodeset;
    xmlNodePtr node;
    int i;

    xml_xpath = mp3tunes_locker_api_simple_fetch(obj, MP3TUNES_SERVER_API, "api/v1/lockerData/", "type", "playlist", NULL);

    mp3tunes_locker_playlist_list_init(playlists);

    if (xml_xpath == NULL) {
        return -1;
    }

    xpath_obj =xml_xpath_query(xml_xpath, "/mp3tunes/playlistList/item");

    if (xpath_obj == NULL) {
        return -1;
    }

    nodeset = xpath_obj->nodesetval;

    for (i = 0; i < nodeset->nodeNr; i++) {
        node = nodeset->nodeTab[i];
        xml_xpath_t* xml_xpath_context = xml_xpath_context_init(xml_xpath, node);
        mp3tunes_locker_playlist_t *playlist = (mp3tunes_locker_playlist_t*)malloc(sizeof(mp3tunes_locker_playlist_t));
        memset(playlist, 0, sizeof(mp3tunes_locker_playlist_t));

        playlist->playlistId = xml_xpath_get_string(xml_xpath_context, "playlistId");
        playlist->playlistTitle = xml_xpath_get_string(xml_xpath_context, "playlistTitle");
        playlist->title = xml_xpath_get_string(xml_xpath_context, "title");
        playlist->fileName = xml_xpath_get_string(xml_xpath_context, "fileName");
        playlist->fileCount = xml_xpath_get_integer(xml_xpath_context, "fileCount");
        playlist->playlistSize = xml_xpath_get_integer(xml_xpath_context, "playlistSize");

        mp3tunes_locker_playlist_list_add(playlists, playlist);
        xml_xpath_deinit(xml_xpath_context);
    }
    xmlXPathFreeObject(xpath_obj);
    xml_xpath_deinit(xml_xpath);
    return 0;
}
