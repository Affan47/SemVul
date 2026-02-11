addIndirectRoot(const Path & path)
{
    string hash = printHash32(hashString(htSHA1, path));
    Path realRoot = canonPath((format("%1%/%2%/auto/%3%")
        % nixStateDir % gcRootsDir % hash).str());
    createSymlink(realRoot, path, false);
}
