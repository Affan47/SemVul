split_sort_mask(unsigned long sort_mask, AWT_QUERY_RESULT_ORDER *order) {


    AWT_QUERY_RESULT_ORDER first = AWT_QUERY_SORT_NONE;

    for (int o = 0; o<MAX_CRITERIA; o++) {
        order[o] = AWT_QUERY_RESULT_ORDER(sort_mask&AWT_QUERY_SORT_CRITERIA_MASK);
        awt_assert(order[o] == (order[o]&AWT_QUERY_SORT_CRITERIA_MASK));

        if (first == AWT_QUERY_SORT_NONE) {
            if (order[o] & (AWT_QUERY_SORT_BY_1STFIELD_CONTENT|AWT_QUERY_SORT_BY_HIT_DESCRIPTION)) {
                first = order[o];
            }
        }

        sort_mask = sort_mask>>AWT_QUERY_SORT_CRITERIA_BITS;
    }
    return first;
}
