err_read(int errid,unsigned errnum)


#ifdef DOC
int             errid     ;
unsigned        errnum    ;
#endif


{

   if( errid < 0 || errid >= MAX_ERROR_OPENS )
      KANIL( "errid out of bounds" );


   if( ErrorStreams[errid] == NULL ) {
      int i=0;
      while(default_errmsgs[i].msg!=NULL&&default_errmsgs[i].id!=errnum) i++;
      if (!default_errmsgs[i].msg) {
          KANIL1( "errnum not found", errnum );
      } else
          return default_errmsgs[i].msg;
      }


   return err_readfile( ErrorStreams[errid], errnum );
}
