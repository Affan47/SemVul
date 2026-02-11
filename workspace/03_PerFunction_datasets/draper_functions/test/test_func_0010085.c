findBaseByNewPath(NewPath* path, BkDir* tree, BkFileBase** base)
{
    BkDir* parentDir;
    bool dirFound;
    BkFileBase* child;


    path->numChildren--;
    dirFound = findDirByNewPath(path, tree, &parentDir);
    path->numChildren++;
    if(!dirFound)
        return false;

    child = parentDir->children;
    while(child != NULL)
    {
        if(strcmp(child->name, path->children[path->numChildren - 1]) == 0)
        {
            *base = child;
            return true;
        }

        child = child->next;
    }

    return false;
}
