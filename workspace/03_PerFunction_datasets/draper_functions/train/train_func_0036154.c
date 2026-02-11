handleDefault(const ICUServiceKey& key, UnicodeString* actualID, UErrorCode& status) const {
        LocaleKey& lkey = (LocaleKey&)key;
        if (actualID) {


            actualID->truncate(0);
        }
        Locale loc("");
        lkey.canonicalLocale(loc);
        return Collator::makeInstance(loc, status);
    }
