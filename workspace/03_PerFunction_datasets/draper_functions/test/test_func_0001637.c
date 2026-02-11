doAdvance( const unsigned int chr, const unsigned int nextChr)
{
  if( !glyphList->Glyph( chr))
  {
    unsigned int g = face.CharIndex( chr);
    glyphList->Add( MakeGlyph( g), g);
  }

  return glyphList->Advance( chr, nextChr);
}
