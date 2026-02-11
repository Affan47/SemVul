FT_OpenType_Free( FT_Face   face,
                    FT_Bytes  table )
  {
    FT_Memory  memory;


    if ( !face )
      return;

    memory = FT_FACE_MEMORY( face );

    FT_FREE( table );
  }
