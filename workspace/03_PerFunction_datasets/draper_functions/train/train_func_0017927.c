mapCharToGlyph(LEUnicode32 ch, const LECharMapper *mapper, le_bool filterZeroWidth) const
{
    LEUnicode32 mappedChar = mapper->mapChar(ch);

    if (mappedChar == 0xFFFE || mappedChar == 0xFFFF) {
        return 0xFFFF;
    }

    if (filterZeroWidth && (mappedChar == 0x200C || mappedChar == 0x200D)) {
        return canDisplay(mappedChar)? 0x0001 : 0xFFFF;
    }

    return mapCharToGlyph(mappedChar);
}
