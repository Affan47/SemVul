dfb_font_destroy( CoreFont *font )
{
     int i;

     D_DEBUG_AT( Core_Font, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( font, CoreFont );

     D_MAGIC_CLEAR( font );

     pthread_mutex_lock( &font->lock );

     dfb_state_set_destination( &font->state, NULL );
     dfb_state_set_source( &font->state, NULL );

     dfb_state_destroy( &font->state );

     direct_hash_iterate( font->glyph_hash, free_glyphs, NULL );

     direct_hash_destroy( font->glyph_hash );

     if (font->rows) {
          for (i = 0; i < font->num_rows; i++) {
               CoreFontCacheRow *row = font->rows[i];

               D_MAGIC_ASSERT( row, CoreFontCacheRow );

               dfb_surface_unref( row->surface );

               D_MAGIC_CLEAR( row );

               D_FREE( row );
          }

          D_FREE( font->rows );
     }

     D_ASSERT( font->encodings != NULL || !font->last_encoding );

     for (i=DTEID_OTHER; i<=font->last_encoding; i++) {
          CoreFontEncoding *encoding = font->encodings[i];

          D_ASSERT( encoding != NULL );
          D_ASSERT( encoding->name != NULL );

          D_MAGIC_CLEAR( encoding );

          D_FREE( encoding->name );
          D_FREE( encoding );
     }

     if (font->encodings)
          D_FREE( font->encodings );

     pthread_mutex_unlock( &font->lock );
     pthread_mutex_destroy( &font->lock );

     D_FREE( font );
}
