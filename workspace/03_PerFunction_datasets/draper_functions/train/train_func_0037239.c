fuzq_initialize_max_distances(FuzzyQuery *fuzq)
{
    int i;
    for (i = 0; i < TYPICAL_LONGEST_WORD; i++) {
        fuzq->max_distances[i] = fuzq_calculate_max_distance(fuzq, i);
    }
}
