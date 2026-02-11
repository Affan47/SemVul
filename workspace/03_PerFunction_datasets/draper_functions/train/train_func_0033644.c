value_create_from_refarray(struct ref_array *raw_lines,
                               struct ref_array *raw_lengths,
                               uint32_t line,
                               uint32_t origin,
                               uint32_t key_len,
                               uint32_t boundary,
                               struct ini_comment *ic,
                               struct value_obj **vo)
{
    int error = EOK;
    struct value_obj *new_vo = NULL;

    TRACE_FLOW_ENTRY();

    if ((!raw_lines) || (!raw_lengths) || (!vo)) {
        TRACE_ERROR_NUMBER("Invalid argument", EINVAL);
        return EINVAL;
    }

    new_vo = malloc(sizeof(struct value_obj));
    if (!new_vo) {
        TRACE_ERROR_NUMBER("No memory", ENOMEM);
        return ENOMEM;
    }


    new_vo->raw_lines = raw_lines;
    new_vo->raw_lengths = raw_lengths;
    new_vo->origin = origin;
    new_vo->line = line;
    new_vo->keylen = key_len;
    new_vo->boundary = boundary;
    new_vo->ic = ic;

    error = value_unfold(new_vo->raw_lines,
                         new_vo->raw_lengths,
                         &(new_vo->unfolded));
    if (error) {
        TRACE_ERROR_NUMBER("Failed to unfold", error);
        value_destroy(new_vo);
        return error;
    }

    TRACE_INFO_STRING("Unfolded:",
                      (const char *)simplebuffer_get_buf(new_vo->unfolded));
    *vo = new_vo;

    TRACE_FLOW_EXIT();

    return error;
}
