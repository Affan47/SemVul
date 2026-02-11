ptr_to_index (SV *sv, const U8 *offset)
{
  return SvUTF8 (sv)
         ? utf8_distance ((U8*)offset, (U8*)SvPVX (sv))
         : offset - (U8*)SvPVX (sv);
}
