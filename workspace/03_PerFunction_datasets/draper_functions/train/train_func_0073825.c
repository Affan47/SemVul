get_file(const char* dataName, int& dataSize)
{
   err_when( !init_flag || !dataName || read_all);

   int i;


	for( i=0 ; i<rec_count ; i++ )
   {
      if( strcmp( index_buf[i].name, dataName ) == 0 )
      {
	 file_seek( index_buf[i].pointer );

	 dataSize = index_buf[i+1].pointer - index_buf[i].pointer;

	 return this;
      }
   }

   return NULL;
}
