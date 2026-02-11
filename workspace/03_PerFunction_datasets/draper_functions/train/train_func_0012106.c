gf_sha1_file( const char *path, u8 output[20] )
{
    FILE *f;
    size_t n;
    GF_SHA1Context *ctx;
    u8 buf[1024];

	if (!strncmp(path, "gmem://", 7)) {
		u32 size;
		u8 *mem_address;
		if (sscanf(path, "gmem://%d@%p", &size, &mem_address) != 2) {
			return GF_IO_ERR;
		}
		gf_sha1_csum(mem_address, size, output);
		return 0;
	}

    if( ( f = gf_f64_open( path, "rb" ) ) == NULL )
        return( 1 );

    ctx  = gf_sha1_starts();

    while( ( n = fread( buf, 1, sizeof( buf ), f ) ) > 0 )
        gf_sha1_update(ctx, buf, (s32) n );

    gf_sha1_finish(ctx, output );

    fclose( f );
    return( 0 );
}
