isMatched(const QString& str, QString *by) const
{

    for (int i = 0; i < shortStringFilters.size(); ++i) {
        if (str.contains(shortStringFilters[i]))
        {
            if (by != 0) *by = shortStringFilters[i];
            return true;
        }
    }

    int len = str.length();
    int k;

    int current = 0;
    int next = 0;

    for (k = 0; k < 8 && k < len; ++k)
        current = (current * HASH_P + str[k].unicode()) % HASH_Q;

    WTF::HashMap<int, QVector<int> >::const_iterator hashEnd = stringFiltersHash.end();

    for (k = 7; k < len; ++k, current = next) {


        if (k + 1 < len)
            next = (HASH_P * ((current + HASH_Q - ((HASH_MOD * str[k - 7].unicode()) % HASH_Q)) % HASH_Q) + str[k + 1].unicode()) % HASH_Q;

        if (!fastLookUp.testBit(current))
            continue;


        WTF::HashMap<int, QVector<int> >::const_iterator it = stringFiltersHash.find(current + 1);


        if (it != hashEnd) {
            for (int j = 0; j < it->second.size(); ++j) {
                int index = it->second[j];

                if (index >= 0) {
                    int flen = stringFilters[index].length();
                    if (k - flen + 1 >= 0 && stringFilters[index] == str.midRef(k - flen + 1 , flen))
                    {
                        if (by != 0) *by = stringFilters[index];
                        return true;
                    }
                } else {
                    index = -index - 1;
                    int flen = rePrefixes[index].length();
                    if (k - 8 + flen < len && rePrefixes[index] == str.midRef(k - 7, flen))
                    {
                        int remStart = k - 7 + flen;
                        QString remainder = QString::fromRawData(str.unicode() + remStart,
                                                                 str.length() - remStart);
                        if (reFilters[index].exactMatch(remainder)) {
                            if (by != 0) *by = rePrefixes[index]+reFilters[index].pattern();
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
