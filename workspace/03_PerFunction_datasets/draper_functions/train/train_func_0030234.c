longest_match_fast(s, cur_match)
    deflate_state *s;
    IPos cur_match;
{
    register Bytef *scan = s->window + s->strstart;
    register Bytef *match;
    register int len;
    register Bytef *strend = s->window + s->strstart + MAX_MATCH;


    Assert(s->hash_bits >= 8 && MAX_MATCH == 258, "Code too clever");

    Assert((ulg)s->strstart <= s->window_size-MIN_LOOKAHEAD, "need lookahead");

    Assert(cur_match < s->strstart, "no future");

    match = s->window + cur_match;


    if (match[0] != scan[0] || match[1] != scan[1]) return MIN_MATCH-1;


    scan += 2, match += 2;
    Assert(*scan == *match, "match[2]?");


    do {
    } while (*++scan == *++match && *++scan == *++match &&
             *++scan == *++match && *++scan == *++match &&
             *++scan == *++match && *++scan == *++match &&
             *++scan == *++match && *++scan == *++match &&
             scan < strend);

    Assert(scan <= s->window+(unsigned)(s->window_size-1), "wild scan");

    len = MAX_MATCH - (int)(strend - scan);

    if (len < MIN_MATCH) return MIN_MATCH - 1;

    s->match_start = cur_match;
    return (uInt)len <= s->lookahead ? (uInt)len : s->lookahead;
}
