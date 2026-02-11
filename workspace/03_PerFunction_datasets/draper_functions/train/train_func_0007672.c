relative(const upath &npath) const {
    if (path().endsWith("/") || npath.path().startsWith("/"))
        return upath(path().append(npath.path()));
    else
        return upath(path().append("/").append(npath.path()));
}
