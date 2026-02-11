do_init
    ( bool compress,
      #if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          bzip2::alloc_func ,
          bzip2::free_func ,
      #endif
      void* derived )
{
    bz_stream* s = static_cast<bz_stream*>(stream_);


        s->bzalloc = 0;
        s->bzfree = 0;

    s->opaque = derived;
    bzip2_error::check BOOST_PREVENT_MACRO_SUBSTITUTION(
        compress ?
            BZ2_bzCompressInit( s,
                                params_.block_size,
                                0,
                                params_.work_factor ) :
            BZ2_bzDecompressInit( s,
                                  0,
                                  params_.small )
    );
    ready_ = true;
}
