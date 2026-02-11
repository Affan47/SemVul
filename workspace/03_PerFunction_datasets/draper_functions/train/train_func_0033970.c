close_compression ( void )
{
   if ( bzip_compress ) {
      bzip_compress->close_compression ( );
      delete bzip_compress;
      bzip_compress = NULL;
   }
}
