_init_pg_stream(BLURAY *bd)
{
    int      pg_subpath = -1;
    unsigned pg_subclip = 0;
    uint16_t pg_pid     = 0;

    bd->st0.pg_pid = 0;

    if (!bd->graphics_controller) {
        return 0;
    }


    gc_run(bd->graphics_controller, GC_CTRL_PG_RESET, 0, NULL);

    if (!bd->decode_pg || !bd->title) {
        return 0;
    }

    _find_pg_stream(bd, &pg_pid, &pg_subpath, &pg_subclip, NULL);


    if (pg_subpath < 0) {
        bd->st0.pg_pid = pg_pid;
        return !!pg_pid;
    }

    return 0;
}
