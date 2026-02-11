ProjectIconIndex(bool read_only)
{
    if (read_only)
        return (int)fvsProjectReadOnly;

    return (int)fvsProject;
}
