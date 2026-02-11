since_last_CF(gconstpointer aa, gconstpointer bb) {
    gint result = 0;
    const Track *a = aa;
    const Track *b = bb;

    if (a && b) {
        result = COMP (b->recent_playcount, a->recent_playcount);
        if (result == 0)
            result = COMP (b->time_played, a->time_played);
        if (result == 0)
            result = COMP (b->playcount, a->playcount);
        if (result == 0)
            result = COMP (b->rating, a->rating);
    }
    return result;
}
