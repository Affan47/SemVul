getGlyphCoverage(LEGlyphID glyphID) const
{
    TTGlyphID ttGlyphID = (TTGlyphID) LE_GET_GLYPH(glyphID);
    le_uint16 count = SWAPW(glyphCount);
    le_uint8 bit = OpenTypeUtilities::highBit(count);
    le_uint16 power = 1 << bit;
    le_uint16 extra = count - power;
    le_uint16 probe = power;
    le_uint16 index = 0;

	if (count == 0) {
		return -1;
	}

    if (SWAPW(glyphArray[extra]) <= ttGlyphID) {
        index = extra;
    }

    while (probe > (1 << 0)) {
        probe >>= 1;

        if (SWAPW(glyphArray[index + probe]) <= ttGlyphID) {
            index += probe;
        }
    }

    if (SWAPW(glyphArray[index]) == ttGlyphID) {
        return index;
    }

    return -1;
}
