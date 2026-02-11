match_expression(const unsigned char *text, const unsigned char *start,
                 bool allowpoison)
{
    const unsigned char *end, *split;
    const unsigned char *p = start;
    bool reverse, escaped;
    bool match = false;
    bool poison = false;
    bool poisoned = false;


    if (!*p)
        return !*text ? UWILDMAT_MATCH : UWILDMAT_FAIL;
    end = start + strlen((const char *) start) - 1;


    for (; p <= end + 1; p = split + 1) {
        if (allowpoison)
            poison = (*p == '@');
        reverse = (*p == '!') || poison;
        if (reverse)
            p++;


        for (escaped = false, split = p; split <= end; split++) {
            if (*split == '[') {
                split++;
                if (*split == ']')
                    split++;
                while (split <= end && *split != ']')
                    split++;
            }
            if (*split == ',' && !escaped)
                break;
            escaped = (*split == '\\') ? !escaped : false;
        }


        if (match == !reverse && poison == poisoned)
            continue;
        if (match_pattern(text, p, split - 1) == true) {
            poisoned = poison;
            match = !reverse;
        }
    }
    if (poisoned)
        return UWILDMAT_POISON;
    return match ? UWILDMAT_MATCH : UWILDMAT_FAIL;
}
