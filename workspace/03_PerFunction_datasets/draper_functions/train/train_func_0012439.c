z_set_window( zword_t w )
{
   int row, col;

   flush_buffer( FALSE );

   screen_window = w;

   if ( screen_window == STATUS_WINDOW )
   {


      formatting = OFF;
      scripting_disable = ON;
      select_status_window(  );


      if ( h_type < V4 )
         move_cursor( 2, 1 );
      else
         move_cursor( 1, 1 );

   }
   else
   {


      select_text_window(  );
      scripting_disable = OFF;
      formatting = ON;


      get_cursor_position( &row, &col );
      if ( row <= status_size )
         move_cursor( status_size + 1, 1 );

   }


   set_attribute( NORMAL );

}
