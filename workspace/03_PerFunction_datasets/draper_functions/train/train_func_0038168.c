HB_GDEF_Get_Glyph_Property( HB_GDEFHeader*  gdef,
				      HB_UShort        glyphID,
				      HB_UShort*       property )
{
  HB_UShort class = 0, index = 0;

  HB_Error  error;


  if ( !gdef || !property )
    return ERR(HB_Err_Invalid_Argument);


  if ( gdef->MarkAttachClassDef.loaded )
  {
    error = _HB_OPEN_Get_Class( &gdef->MarkAttachClassDef, glyphID, &class, &index );
    if ( error && error != HB_Err_Not_Covered )
      return error;
    if ( !error )
    {
      *property = class << 8;
      return HB_Err_Ok;
    }
  }

  error = _HB_OPEN_Get_Class( &gdef->GlyphClassDef, glyphID, &class, &index );
  if ( error && error != HB_Err_Not_Covered )
    return error;


  if ( error == HB_Err_Not_Covered && gdef->NewGlyphClasses )
    class = Get_New_Class( gdef, glyphID, index );

  switch ( class )
  {
  default:
  case UNCLASSIFIED_GLYPH:
    *property = 0;
    break;

  case SIMPLE_GLYPH:
    *property = HB_GDEF_BASE_GLYPH;
    break;

  case LIGATURE_GLYPH:
    *property = HB_GDEF_LIGATURE;
    break;

  case MARK_GLYPH:
    *property = HB_GDEF_MARK;
    break;

  case COMPONENT_GLYPH:
    *property = HB_GDEF_COMPONENT;
    break;
  }

  return HB_Err_Ok;
}
