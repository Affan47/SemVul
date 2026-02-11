toNativeFilename() const throw(BadURIException) {
    gchar *uriString = toString();
    if (isRelativePath()) {
        return uriString;
    } else {
        gchar *filename = g_filename_from_uri(uriString, NULL, NULL);
        g_free(uriString);
        if (filename) {
            return filename;
        } else {
            throw MalformedURIException();
        }
    }
}
