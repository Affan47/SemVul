doParse(const UnicodeString& text,
                ParsePosition& parsePosition,
                double baseValue,
                double ,
                UBool lenientParse,
                Formattable& resVal) const
{


    if (!byDigits) {
        return NFSubstitution::doParse(text, parsePosition, baseValue, 0, lenientParse, resVal);


    } else {
        UnicodeString workText(text);
        ParsePosition workPos(1);
        double result = 0;
        int32_t digit;


        DigitList dl;
        NumberFormat* fmt = NULL;
        while (workText.length() > 0 && workPos.getIndex() != 0) {
            workPos.setIndex(0);
            Formattable temp;
            getRuleSet()->parse(workText, workPos, 10, temp);
            UErrorCode status = U_ZERO_ERROR;
            digit = temp.getLong(status);


            if (lenientParse && workPos.getIndex() == 0) {
                if (!fmt) {
                    status = U_ZERO_ERROR;
                    fmt = NumberFormat::createInstance(status);
                    if (U_FAILURE(status)) {
                        delete fmt;
                        fmt = NULL;
                    }
                }
                if (fmt) {
                    fmt->parse(workText, temp, workPos);
                    digit = temp.getLong(status);
                }
            }

            if (workPos.getIndex() != 0) {
                dl.append((char)('0' + digit));


                parsePosition.setIndex(parsePosition.getIndex() + workPos.getIndex());
                workText.removeBetween(0, workPos.getIndex());
                while (workText.length() > 0 && workText.charAt(0) == gSpace) {
                    workText.removeBetween(0, 1);
                    parsePosition.setIndex(parsePosition.getIndex() + 1);
                }
            }
        }
        delete fmt;

        result = dl.fCount == 0 ? 0 : dl.getDouble();
        result = composeRuleValue(result, baseValue);
        resVal.setDouble(result);
        return TRUE;
    }
}
