Write(const char *key, const CPLString &file_name) {
    CPLString cache_file(KeyToCacheFile(key));

    if (CPLCopyFile(cache_file.c_str(), file_name.c_str()) != CE_None) {
        MakeDirs(cache_file.c_str());
        CPLCopyFile(cache_file.c_str(), file_name.c_str());
    }

    return CE_None;
}
