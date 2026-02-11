unpack( char *& buffer, const VT_MPI_INT & bufferSize,
                         VT_MPI_INT & bufferPos )
{
   DefRec_BaseS::unpack( buffer, bufferSize, bufferPos );


   uint32_t name_length;
   CALL_MPI( MPI_Unpack( buffer, bufferSize, &bufferPos, &name_length, 1,
                         MPI_UNSIGNED, MPI_COMM_WORLD ) );


   char * c_name = new char[name_length+1];
   vt_assert( c_name );
   CALL_MPI( MPI_Unpack( buffer, bufferSize, &bufferPos, c_name,
                         name_length + 1, MPI_CHAR, MPI_COMM_WORLD ) );
   name = c_name;
   delete [] c_name;


   CALL_MPI( MPI_Unpack( buffer, bufferSize, &bufferPos, &group, 1,
                         MPI_UNSIGNED, MPI_COMM_WORLD ) );
}
