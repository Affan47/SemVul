Open( const char* fontname, bool p)
{
  preCache = p;

  if( face.Open( fontname))
  {
    FT_Face* ftFace = face.Face();
    numGlyphs = (*ftFace)->num_glyphs;

    return true;
  }
  else
  {
    err = face.Error();
    return false;
  }
}
