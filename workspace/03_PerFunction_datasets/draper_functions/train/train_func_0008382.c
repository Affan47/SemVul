FT_Init_FreeType( FT_Library  *alibrary )
  {
    FT_Error   error;
    FT_Memory  memory;


    memory = FT_New_Memory();
    if ( !memory )
    {
      FT_ERROR(( "FT_Init_FreeType: cannot find memory manager\n" ));
      return FT_THROW( Unimplemented_Feature );
    }


    error = FT_New_Library( memory, alibrary );
    if ( error )
      FT_Done_Memory( memory );
    else
      FT_Add_Default_Modules( *alibrary );

    return error;
  }
