AddInvertedCharacterRanges(RECharSet *charSet,
                           const CharacterRange *range,
                           const CharacterRange *end)
{
    uint16 previous = 0;
    for (; range < end; ++range) {
        AddCharacterRangeToCharSet(charSet, previous, range->start - 1);
        previous = range->end + 1;
    }
    AddCharacterRangeToCharSet(charSet, previous, charSet->length);
}
