_mvefile_open(MVEFILE *file, void *stream)
{
    file->stream = stream;
    if (! file->stream)
        return 0;

    return 1;
}
