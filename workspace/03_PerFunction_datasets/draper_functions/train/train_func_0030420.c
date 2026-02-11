formatAndAppend(const Format* formatter, const Formattable& arg,
                         const UnicodeString &argString, UErrorCode& ec) {
        if (!argString.isEmpty()) {
            if (U_SUCCESS(ec)) {
                append(argString);
            }
        } else {
            formatAndAppend(formatter, arg, ec);
        }
    }
