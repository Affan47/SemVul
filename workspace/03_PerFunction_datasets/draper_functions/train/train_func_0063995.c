extract_nglyphs(const Substitute &s, uint8_t t, bool coverage_ok) throw ()
{
    switch (t) {
      case T_GLYPH:
	return 1;
      case T_GLYPHS:
	return s.gids[0];
      case T_COVERAGE:
	return (coverage_ok ? 1 : 0);
      default:
	return 0;
    }
}
