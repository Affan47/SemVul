open( const char* fileName, int bufferAll )
{
   close();

   file_open(fileName);
   file_read( &dbf_header, sizeof(DbfHeader) );


   if( bufferAll )
   {
      dbf_buf = mem_add( dbf_header.rec_size * dbf_header.last_rec );

      file_seek( 1 + dbf_header.data_offset );
      file_read( dbf_buf, dbf_header.rec_size*dbf_header.last_rec );
      file_close();

      dbf_buf_allocated = 1;
   }
   else
      rec_buf = mem_add( dbf_header.rec_size );

   cur_recno = 1;
}
