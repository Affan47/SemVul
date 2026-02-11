scroll_line(  )
{
   int row, col;
   int i;

   get_cursor_position( &row, &col );

   if ( *CS || row < screen_rows )
   {
      for ( i = col; i < screen_cols; i++ )
         outc( ' ' );
      display_char( '\n' );
   }
   else
   {
      move_cursor( status_size + 1, 1 );
      tputs( DL, 1, outc );
      move_cursor( row, 1 );
      for ( i = col; i < screen_cols; i++ )
         outc( ' ' );
   }

   current_col = 1;
   if ( ++current_row > screen_rows )
   {
      current_row = screen_rows;
      move_cursor( current_row, 1 );
      for ( i = 1; i < screen_cols; i++ )
         outc( ' ' );
      move_cursor( current_row, 1 );
   }

}
