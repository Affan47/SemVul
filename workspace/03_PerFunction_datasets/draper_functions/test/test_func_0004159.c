dfb_font_decode_character( CoreFont          *font,
                           DFBTextEncodingID  encoding,
                           u32                character,
                           unsigned int      *ret_index )
{
     D_DEBUG_AT( Core_Font, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( font, CoreFont );
     D_ASSERT( ret_index != NULL );

     if (encoding > font->last_encoding)
          return DFB_IDNOTFOUND;

     if (encoding != DTEID_UTF8) {
          D_ASSERT( font->encodings[encoding] != NULL );
          D_ASSERT( font->encodings[encoding]->funcs != NULL );
          D_ASSERT( font->encodings[encoding]->funcs->GetCharacterIndex != NULL );

          return font->encodings[encoding]->funcs->GetCharacterIndex( font, character, ret_index );
     }
     else if (font->utf8) {
          const CoreFontEncodingFuncs *funcs = font->utf8;

          D_ASSERT( funcs->GetCharacterIndex != NULL );

          return funcs->GetCharacterIndex( font, character, ret_index );
     }
     else
          *ret_index = character;

     return DFB_OK;
}
