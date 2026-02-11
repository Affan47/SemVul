AddGLTextLine(const char *keyword, const char *value)
{
  lump_t *gl_level;


  if (! wad.current_level->lev_info->buddy)
    CreateGLMarker();

  gl_level = wad.current_level->lev_info->buddy;

# if DEBUG_KEYS
  PrintDebug("[%s] Adding: %s=%s\n", gl_level->name, keyword, value);
# endif

  AppendLevelLump(gl_level, keyword, (int)strlen(keyword));
  AppendLevelLump(gl_level, "=", 1);

  AppendLevelLump(gl_level, value, (int)strlen(value));
  AppendLevelLump(gl_level, "\n", 1);
}
