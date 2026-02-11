diff_operations (CutDiffer *differ, CutDiffWriter *writer,
                 const GList *operations, gchar **from, gchar **to)
{
    for (; operations; operations = g_list_next(operations)) {
        CutSequenceMatchOperation *operation = operations->data;

        switch (operation->type) {
        case CUT_SEQUENCE_MATCH_OPERATION_EQUAL:
            mark_equal(writer, from,
                       operation->from_begin, operation->from_end);
            break;
        case CUT_SEQUENCE_MATCH_OPERATION_INSERT:
            mark_inserted(writer, to,
                          operation->to_begin, operation->to_end);
            break;
        case CUT_SEQUENCE_MATCH_OPERATION_DELETE:
            mark_deleted(writer, from,
                         operation->from_begin, operation->from_end);
            break;
        case CUT_SEQUENCE_MATCH_OPERATION_REPLACE:
            diff_lines(differ, writer,
                       from, operation->from_begin, operation->from_end,
                       to, operation->to_begin, operation->to_end);
            break;
        default:
            g_error("unknown operation type: %d", operation->type);
            break;
        }
    }
}
