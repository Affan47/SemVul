z_save( int argc, zword_t table, zword_t bytes, zword_t name )
{
   char new_name[Z_FILENAME_MAX + Z_PATHNAME_MAX + 1];
   char default_name[Z_FILENAME_MAX + Z_PATHNAME_MAX + 1];
   FILE *afp;

#if defined BUFFER_FILES
   char afpbuffer[BUFSIZ];
#endif
   int status = 0;

   if ( argc == 3 )
   {
      get_default_name( default_name, name );
      if ( get_file_name( new_name, default_name, GAME_SAVE_AUX ) != 0 )
      {
         goto finished;
      }

      if ( ( afp = fopen( new_name, "wb" ) ) == NULL )
      {
         goto finished;
      }

#if defined BUFFER_FILES
      setbuf( afp, afpbuffer );
#endif

      status = fwrite( datap + table, bytes, 1, afp );

      fclose( afp );

      if ( status != 0 )
      {
         strcpy( auxilary_name, default_name );
      }

      status = !status;
   }
   else
   {

      status = 1;

      if ( get_file_name( new_name, save_name, GAME_SAVE ) == 0 )
      {

         if ( save_restore( new_name, GAME_SAVE ) == 0 )
         {

            file_cleanup( new_name, GAME_SAVE );


            strcpy( save_name, new_name );


            status = 0;
         }
      }
   }

 finished:


   if ( h_type < V4 )
   {
      conditional_jump( status == 0 );
   }
   else
   {
      store_operand( (zword_t)(( status == 0 ) ? 1 : 0) );
   }

   return ( status );
}
