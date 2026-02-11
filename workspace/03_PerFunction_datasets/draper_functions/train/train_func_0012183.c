write_rectangle( File, Name, X, Y, Dx, Dy, Layer, WriteLayer )

     FILE *File;
     char *Name;
     long  X;
     long  Y;
     long  Dx;
     long  Dy;
     char *Layer;
     char  WriteLayer;
  {
    if ( WriteLayer )
    {
      (void)fprintf( File, "L%s;\n", Layer );
    }

    if ( (  Name != (char *)NULL ) &&
         ( *Name != '*'          ) &&
         ( *Name != '\0'         ) )
    {
      if ( ! RDS_CIF_BERKLEY_DRIVER )
      {
        (void)fprintf( File, "4N %s %ld %ld;\n",
                       rdstocifname( Name ),
                       RDS_TO_CIF_UNIT(  X ) + RDS_TO_CIF_UNIT( Dx ) / 2,
                       RDS_TO_CIF_UNIT(  Y ) + RDS_TO_CIF_UNIT( Dy ) / 2);
      }
      else
      {
      (void)fprintf( File, "95 %s %ld %ld %ld %ld %s;\n",
                     rdstocifname( Name ),
                     RDS_TO_CIF_UNIT( Dx ), RDS_TO_CIF_UNIT( Dy ),
                     RDS_TO_CIF_UNIT(  X ) + RDS_TO_CIF_UNIT( Dx ) / 2,
                     RDS_TO_CIF_UNIT(  Y ) + RDS_TO_CIF_UNIT( Dy ) / 2,
                     Layer );
      }
    }

    (void)fprintf( File, "B%ld %ld %ld %ld;\n",
                   RDS_TO_CIF_UNIT( ABSOLUTE( Dx ) ),
                   RDS_TO_CIF_UNIT( ABSOLUTE( Dy ) ),
                   RDS_TO_CIF_UNIT(  X ) + RDS_TO_CIF_UNIT( Dx ) / 2,
                   RDS_TO_CIF_UNIT(  Y ) + RDS_TO_CIF_UNIT( Dy ) / 2);
  }
