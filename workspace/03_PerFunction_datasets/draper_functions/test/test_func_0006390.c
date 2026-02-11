determine_operation_type (guint from_index, guint to_index,
                          CutSequenceMatchInfo *info)
{
    if (from_index < info->from_index && to_index < info->to_index) {
        return CUT_SEQUENCE_MATCH_OPERATION_REPLACE;
    } else if (from_index < info->from_index) {
        return CUT_SEQUENCE_MATCH_OPERATION_DELETE;
    } else if (to_index < info->to_index) {
        return CUT_SEQUENCE_MATCH_OPERATION_INSERT;
    } else {
        return CUT_SEQUENCE_MATCH_OPERATION_EQUAL;
    }
}
