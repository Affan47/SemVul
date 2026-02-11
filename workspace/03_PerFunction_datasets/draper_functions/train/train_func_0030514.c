findRoots(bool deleteStale)
{
    Roots roots;
    Path rootsDir = canonPath((format("%1%/%2%") % nixStateDir % gcRootsDir).str());
    findRoots(rootsDir, true, deleteStale, roots);
    return roots;
}
