topoSortPaths(const PathSet & paths)
{
    Paths sorted;
    PathSet visited;
    foreach (PathSet::const_iterator, i, paths)
        dfsVisit(paths, *i, visited, sorted);
    return sorted;
}
