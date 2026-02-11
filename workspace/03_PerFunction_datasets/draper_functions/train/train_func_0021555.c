toNativeSeparators(const std::string &path)
{
#if defined(_WIN32)
    char separ = '/';
    char native = '\\';
#else
    char separ = '\\';
    char native = '/';
#endif
    std::string modified(path);
    std::replace(modified.begin(), modified.end(), separ, native);
    return modified;
}
