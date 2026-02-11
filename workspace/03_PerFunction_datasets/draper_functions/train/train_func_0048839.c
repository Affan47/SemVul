appendAffixPattern(UnicodeString& appendTo,
                                       const UnicodeString* affixPattern,
                                       const UnicodeString& expAffix,
                                       UBool localized) const {
    if (affixPattern == 0) {
        appendAffixPattern(appendTo, expAffix, localized);
    } else {
        int i;
        for (int pos=0; pos<affixPattern->length(); pos=i) {
            i = affixPattern->indexOf(kQuote, pos);
            if (i < 0) {
                UnicodeString s;
                affixPattern->extractBetween(pos, affixPattern->length(), s);
                appendAffixPattern(appendTo, s, localized);
                break;
            }
            if (i > pos) {
                UnicodeString s;
                affixPattern->extractBetween(pos, i, s);
                appendAffixPattern(appendTo, s, localized);
            }
            UChar32 c = affixPattern->char32At(++i);
            ++i;
            if (c == kQuote) {
                appendTo.append(c).append(c);

            } else if (c == kCurrencySign &&
                       i<affixPattern->length() &&
                       affixPattern->char32At(i) == kCurrencySign) {
                ++i;
                appendTo.append(c).append(c);
            } else if (localized) {
                switch (c) {
                case kPatternPercent:
                    appendTo += getConstSymbol(DecimalFormatSymbols::kPercentSymbol);
                    break;
                case kPatternPerMill:
                    appendTo += getConstSymbol(DecimalFormatSymbols::kPerMillSymbol);
                    break;
                case kPatternPlus:
                    appendTo += getConstSymbol(DecimalFormatSymbols::kPlusSignSymbol);
                    break;
                case kPatternMinus:
                    appendTo += getConstSymbol(DecimalFormatSymbols::kMinusSignSymbol);
                    break;
                default:
                    appendTo.append(c);
                }
            } else {
                appendTo.append(c);
            }
        }
    }
}
