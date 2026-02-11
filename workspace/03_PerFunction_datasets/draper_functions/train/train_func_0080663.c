fm_path_depth(FmPath* path)
{
    int depth = 1;
    while(path->parent)
    {
        ++depth;
        path = path->parent;
    }
    return depth;
}
