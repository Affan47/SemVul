spawn_read(spawn_t sp, char* buffer, size_t bufsize)
{
    if(!spawn_ok(sp))
        return 0;
    return read(sp.pipe[0], buffer, bufsize);
}
