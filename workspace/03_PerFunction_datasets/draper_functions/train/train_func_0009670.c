state_set_equal(const struct state_set *set1,
                           const struct state_set *set2) {
    if (set1->used != set2->used)
        return 0;
    if (set1->sorted && set2->sorted) {
        for (int i = 0; i < set1->used; i++)
            if (set1->states[i] != set2->states[i])
                return 0;
        return 1;
    } else {
        for (int i=0; i < set1->used; i++)
            if (state_set_index(set2, set1->states[i]) == -1)
                return 0;
        return 1;
    }
}
