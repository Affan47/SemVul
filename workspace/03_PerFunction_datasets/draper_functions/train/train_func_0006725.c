cpl_frameset_erase_frame(cpl_frameset *self, cpl_frame *frame)
{

    const cxchar *const _id = "cpl_frameset_erase_frame";

    cx_multimap_iterator first, last;


    if (self == NULL) {
        cpl_error_set(_id, CPL_ERROR_NULL_INPUT);
        return CPL_ERROR_NULL_INPUT;
    }

    if (!frame) {
        return CPL_ERROR_NONE;
    }

    first = cx_multimap_lower_bound(self->frames, cpl_frame_get_tag(frame));
    last = cx_multimap_upper_bound(self->frames, cpl_frame_get_tag(frame));

    while (first != last) {
        if (cx_multimap_get_value(self->frames, first) == frame) {

            if (_cpl_frameset_cache_get(self, TAG) == first) {

                cx_multimap_iterator p;

                p = cx_multimap_previous(self->frames, first);

                if (p == cx_multimap_end(self->frames)) {
                    p = cx_multimap_begin(self->frames);
                }

                _cpl_frameset_cache_push(self, TAG, p);
            }

            if (_cpl_frameset_cache_get(self, POS) == first) {

                cx_list_iterator p = cx_list_begin(self->history);

                while (cx_list_get(self->history, p) != first &&
                       p != cx_list_end(self->history)) {
                    p = cx_list_next(self->history, p);
                }

                cx_assert(p != cx_list_end(self->history));
                p = cx_list_previous(self->history, p);

                if (p == cx_list_end(self->history)) {
                    p = cx_list_begin(self->history);
                }

                _cpl_frameset_cache_push(self, POS,
                                         cx_list_get(self->history, p));

            }

            cx_multimap_erase_position(self->frames, first);
            cx_list_remove(self->history, first);
            break;
        }

        first = cx_multimap_next(self->frames, first);
    }

    return CPL_ERROR_NONE;

}
