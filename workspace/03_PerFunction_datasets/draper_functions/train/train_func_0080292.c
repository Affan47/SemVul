__wb_mark_unwind_till (list_head_t *list, list_head_t *unwinds, size_t size)
{
        size_t        written_behind = 0;
        wb_request_t *request        = NULL;
        wb_file_t    *file           = NULL;

        if (list_empty (list)) {
                goto out;
        }

        request = list_entry (list->next, typeof (*request), list);
        file = request->file;

        list_for_each_entry (request, list, list)
        {
                if ((request->stub == NULL)
                    || (request->stub->fop != GF_FOP_WRITE)) {
                        continue;
                }

                if (written_behind <= size) {
                        if (!request->flags.write_request.write_behind) {
                                written_behind += request->write_size;
                                request->flags.write_request.write_behind = 1;
                                list_add_tail (&request->unwinds, unwinds);

                                if (!request->flags.write_request.got_reply) {
                                        file->window_current
                                                += request->write_size;
                                }
                        }
                } else {
                        break;
                }
        }

out:
        return written_behind;
}
