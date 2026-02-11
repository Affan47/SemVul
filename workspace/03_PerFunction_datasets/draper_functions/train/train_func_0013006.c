parseRules(UnicodeString& description, const RuleBasedNumberFormat* owner, UErrorCode& status)
{


    if (U_FAILURE(status)) {
        return;
    }


    UnicodeString currentDescription;
    int32_t oldP = 0;
    while (oldP < description.length()) {
        int32_t p = description.indexOf(gSemicolon, oldP);
        if (p == -1) {
            p = description.length();
        }
        currentDescription.setTo(description, oldP, p - oldP);
        NFRule::makeRules(currentDescription, this, rules.last(), owner, rules, status);
        oldP = p + 1;
    }


    int64_t defaultBaseValue = 0;


    uint32_t i = 0;
    while (i < rules.size()) {
        NFRule* rule = rules[i];

        switch (rule->getType()) {


        case NFRule::kNoBase:
            rule->setBaseValue(defaultBaseValue, status);
            if (!isFractionRuleSet()) {
                ++defaultBaseValue;
            }
            ++i;
            break;


        case NFRule::kNegativeNumberRule:
            negativeNumberRule = rules.remove(i);
            break;


        case NFRule::kImproperFractionRule:
            fractionRules[0] = rules.remove(i);
            break;


        case NFRule::kProperFractionRule:
            fractionRules[1] = rules.remove(i);
            break;


        case NFRule::kMasterRule:
            fractionRules[2] = rules.remove(i);
            break;


        default:
            if (rule->getBaseValue() < defaultBaseValue) {

                status = U_PARSE_ERROR;
                return;
            }
            defaultBaseValue = rule->getBaseValue();
            if (!isFractionRuleSet()) {
                ++defaultBaseValue;
            }
            ++i;
            break;
        }
    }
}
