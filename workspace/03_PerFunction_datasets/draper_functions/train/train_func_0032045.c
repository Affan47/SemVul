isStorePath(const Path & path)
{
    return isInStore(path)
        && path.find('/', nixStore.size() + 1) == Path::npos;
}
