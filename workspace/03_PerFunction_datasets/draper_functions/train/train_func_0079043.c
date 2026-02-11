operator==(const Format& other) const
{
    if (this == &other) {
        return TRUE;
    }

    if (typeid(*this) == typeid(other)) {
        const RuleBasedNumberFormat& rhs = (const RuleBasedNumberFormat&)other;
        if (locale == rhs.locale &&
            lenient == rhs.lenient &&
            (localizations == NULL
                ? rhs.localizations == NULL
                : (rhs.localizations == NULL
                    ? FALSE
                    : *localizations == rhs.localizations))) {

            NFRuleSet** p = ruleSets;
            NFRuleSet** q = rhs.ruleSets;
            if (p == NULL) {
                return q == NULL;
            } else if (q == NULL) {
                return FALSE;
            }
            while (*p && *q && (**p == **q)) {
                ++p;
                ++q;
            }
            return *q == NULL && *p == NULL;
        }
    }

    return FALSE;
}
