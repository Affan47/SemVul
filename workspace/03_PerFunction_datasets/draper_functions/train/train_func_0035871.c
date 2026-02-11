findArchiveDirEntry(char *pathname, ZipFile *zip) {
    char *found;


    findHashEntry((*zip->dir_hash), pathname, found, FALSE, FALSE, FALSE);

    return found;
}
