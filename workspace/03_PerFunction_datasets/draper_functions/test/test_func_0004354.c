assign(Substitute &s, uint8_t &t, const Substitute &os, uint8_t ot)
{
    if (&s == &os)
	return;
    switch (ot) {
      case T_NONE:
	clear(s, t);
	break;
      case T_GLYPH:
	assign(s, t, os.gid);
	break;
      case T_GLYPHS:
	assign(s, t, os.gids[0], os.gids + 1);
	break;
      case T_COVERAGE:
	assign(s, t, *os.coverage);
	break;
      default:
	assert(0);
    }
}
