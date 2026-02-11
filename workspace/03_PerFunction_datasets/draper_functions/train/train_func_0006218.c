deleteDataOfKey(GBDATA *gbd, GBQUARK key_quark, StringSet& deletedData, long& deleted, long& notDeleted) {
    GB_ERROR error = 0;
    for (GBDATA *gb_sub = GB_child(gbd); gb_sub; gb_sub = GB_nextChild(gb_sub)) {
        switch (GB_read_type(gb_sub)) {
            case GB_DB:
                error = deleteDataOfKey(gb_sub, key_quark, deletedData, deleted, notDeleted);
                break;

            case GB_STRING:
            case GB_LINK:
                if (GB_get_quark(gb_sub) == key_quark) {
                    if (GB_is_directory_compressed(gb_sub)) {
                        string path(GB_get_db_path(gb_sub));
                        error = GB_delete(gb_sub);
                        if (!error) {
                            deletedData.insert(path);
                            deleted++;
                        }
                    }
                    else {
                        notDeleted++;
                    }
                }
                break;
            default :
                break;
        }
    }
    return error;
}
