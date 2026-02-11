dfb_gfxcard_drawstring_check_state( CoreFont *font, CardState *state )
{
     int            i;
     CoreGlyphData *data = NULL;

     D_ASSERT( card != NULL );
     D_ASSERT( card->shared != NULL );
     D_MAGIC_ASSERT( state, CardState );
     D_ASSERT( font != NULL );

     D_DEBUG_AT( Core_GfxState, "%s( %p, %p ) <- font state %p\n", __FUNCTION__, font, state, &font->state );

     dfb_font_lock( font );

     for (i=0; i<128; i++) {
          if (dfb_font_get_glyph_data (font, i, &data) == DFB_OK)
               break;
     }

     if (!data) {
          D_DEBUG_AT( Core_GfxState, "  -> No font data!\n" );
          dfb_font_unlock( font );
          return;
     }

     setup_font_state( font, state );


     dfb_state_set_source( &font->state, data->surface );


     if (dfb_gfxcard_state_check( &font->state, DFXL_BLIT ))
          state->accel |= DFXL_DRAWSTRING;
     else
          state->accel &= ~DFXL_DRAWSTRING;

     dfb_font_unlock( font );
}
