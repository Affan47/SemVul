SimplifyFlags(char * prgbFlags, int cnPoints)
{
	for (int i = 0; i < cnPoints; i++)
		prgbFlags[i] = static_cast<char>(prgbFlags[i] & Sfnt::SimpleGlyph::OnCurve);
	return true;
}
