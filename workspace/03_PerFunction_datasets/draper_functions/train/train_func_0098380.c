printsod( FILE *stream, size_t len )
{
  (void)fseeko(stream, (off_t)len, SEEK_CUR);
  if( len )
    {
    fprintf(fout,"\n" );
    fprintf(fout,"Data : %zu bytes\n", len );
    data_size += len;
    }
}
