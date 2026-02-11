fetch_song_info(SongData &data)
{
    if (access(data.get_path().c_str(), R_OK))
        return false;

    AutoTransaction at;
    if (!data.get_song_from_playlist())
    {
        if (!identify_playlist_item(data.position))
            return false;
        data.get_song_from_playlist();
    }
    at.commit();

    if (!data.isok()) {
        LOG(INFO) << "Fetch failed: " << data.get_path() << endl;
        return false;
    }

    StringPair info = data.get_info();

    const string &artist = info.first;
    const string &title = info.second;

    if (artist != "" && title != "")
        data.identified = true;
    else if ((data.identified = parse_song_info(data, info)))
        data.set_info(info);

    data.rating = data.get_rating();

#if defined(DEBUG) && 0
    cerr << "path:\t" << data.get_path() << endl;
    cerr << "artist:\t" << artist << endl;
    cerr << "title:\t" << title << endl;
#endif

    data.last_played = time(0) - data.get_last();

    return true;
}
