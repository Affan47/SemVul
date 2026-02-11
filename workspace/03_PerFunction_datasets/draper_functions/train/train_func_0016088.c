readStorePaths(Source & from)
{
    PathSet paths = readStringSet(from);
    foreach (PathSet::iterator, i, paths) assertStorePath(*i);
    return paths;
}
