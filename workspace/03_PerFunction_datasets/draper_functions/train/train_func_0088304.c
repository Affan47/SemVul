substitute_in(const Substitute &s, uint8_t t, const Coverage &c)
{
    switch (t) {
      case T_NONE:
	return true;
      case T_GLYPH:
	return c.covers(s.gid);
      case T_GLYPHS:
	for (int i = 1; i <= s.gids[0]; i++)
	    if (!c.covers(s.gids[i]))
		return false;
	return true;
      case T_COVERAGE:
	return *s.coverage <= c;
      default:
	assert(0);
	return false;
    }
}
