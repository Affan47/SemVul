x264_malloc( int i_size )
{
    uint8_t *align_buf = NULL;
#if SYS_MACOSX || (SYS_WINDOWS && ARCH_X86_64)

    align_buf = malloc( i_size );
#elif HAVE_MALLOC_H
    align_buf = memalign( 16, i_size );
#else
    uint8_t *buf = malloc( i_size + 15 + sizeof(void **) );
    if( buf )
    {
        align_buf = buf + 15 + sizeof(void **);
        align_buf -= (intptr_t) align_buf & 15;
        *( (void **) ( align_buf - sizeof(void **) ) ) = buf;
    }
#endif
    if( !align_buf )
        x264_log( NULL, X264_LOG_ERROR, "malloc of size %d failed\n", i_size );
    return align_buf;
}
