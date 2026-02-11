AddCharacterRanges(RECharSet *charSet,
                   const CharacterRange *range,
                   const CharacterRange *end)
{
    for (; range < end; ++range)
        AddCharacterRangeToCharSet(charSet, range->start, range->end);
}
