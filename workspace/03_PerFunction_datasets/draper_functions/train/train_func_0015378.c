Face_Destroy( PFace face )
  {
    if ( face ) {
        ttfMemory *mem = face->font->tti->ttf_memory;


        FREE( face->cvt );
        face->cvtSize = 0;


        FREE( face->fontProgram );
        FREE( face->cvtProgram );
        face->fontPgmSize = 0;
        face->cvtPgmSize  = 0;
    }
    return TT_Err_Ok;
  }
