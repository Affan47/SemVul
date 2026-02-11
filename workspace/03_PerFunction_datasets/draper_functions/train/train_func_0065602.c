rb_inflate_sync_point_p(VALUE obj)
{
    struct zstream *z = get_zstream(obj);
    int err;

    err = inflateSyncPoint(&z->stream);
    if (err == 1) {
	return Qtrue;
    }
    if (err != Z_OK) {
	raise_zlib_error(err, z->stream.msg);
    }
    return Qfalse;
}
