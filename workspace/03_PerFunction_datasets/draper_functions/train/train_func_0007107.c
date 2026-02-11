z_set_font( zword_t new_font )
{
   zword_t old_font = font;

   if ( new_font != old_font )
   {
      font = new_font;
      set_font( font );
   }

   store_operand( old_font );

}
