writedata ( const void* buf, int size ) {
   const char* c = (const char*)buf;
   for ( int i = 0; i < size; ++i )
      put ( c[i] );
}
