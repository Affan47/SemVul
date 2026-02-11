PS_test_sets_on_path( float &_distance ) {
    long count_matched_source = 0;
    long count_matched_target = 0;
    SpeciesID  path_id;
    IDSetCIter path_end   = __PATH.end();
    IDSetCIter path       = __PATH.begin();
    IDSetCIter source_end = __SOURCE_ID_SET.end();
    IDSetCIter source     = __SOURCE_ID_SET.begin();
    PS_BitSet::IndexSet::const_iterator target_end = __TARGET_ID_SET.end();
    PS_BitSet::IndexSet::const_iterator target     = __TARGET_ID_SET.begin();

    while (path != path_end) {
        path_id = *path;
        while ((*target < path_id) && (target != target_end)) {
            ++target;
        }
        if ((target != target_end) && (*target == path_id))
            ++count_matched_target;
        while ((*source < path_id) && (source != source_end)) {
            ++source;
        }
        if ((source != source_end) && (*source == path_id))
            ++count_matched_source;
        ++path;
    }

    if ((count_matched_source > __SOURCE_MIN_MATCH_COUNT) &&
        (count_matched_source < __SOURCE_MAX_MATCH_COUNT) &&
        (count_matched_target > __TARGET_MIN_MATCH_COUNT) &&
        (count_matched_target < __TARGET_MAX_MATCH_COUNT)) {
        _distance = fabs( __SOURCE_PERFECT_MATCH_COUNT - count_matched_source ) + fabs( __TARGET_PERFECT_MATCH_COUNT - count_matched_target );
        return true;
    }
    return false;
}
