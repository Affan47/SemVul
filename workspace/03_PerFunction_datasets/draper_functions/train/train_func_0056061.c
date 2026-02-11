IDirectFBFont_EnumEncodings( IDirectFBFont           *thiz,
                             DFBTextEncodingCallback  callback,
                             void                    *context )
{
     int       i;
     CoreFont *font;

     DIRECT_INTERFACE_GET_DATA(IDirectFBFont)

     if (!callback)
          return DFB_INVARG;

     D_DEBUG_AT( Font, "%s( %p, %p, %p )\n", __FUNCTION__, thiz, callback, context );

     font = data->font;

     if (callback( DTEID_UTF8, "UTF8", context ) == DFENUM_OK) {
          for (i=DTEID_OTHER; i<=font->last_encoding; i++) {
               if (callback( i, font->encodings[i]->name, context ) != DFENUM_OK)
                    break;
          }
     }

     return DFB_OK;
}
