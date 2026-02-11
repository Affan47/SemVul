gl_print_uncollated_merge_sheet (glLabel          *label,
                                 cairo_t          *cr,
                                 gint              page,
                                 gint              n_copies,
                                 gint              first,
                                 gboolean          outline_flag,
                                 gboolean          reverse_flag,
                                 gboolean          crop_marks_flag,
                                 glPrintState     *state)
{
	glMerge                   *merge;
	const GList               *record_list;
	PrintInfo                 *pi;
	const lglTemplateFrame    *frame;
	gint                       i_label, n_labels_per_page, i_copy;
	glMergeRecord             *record;
	GList                     *p;
	lglTemplateOrigin         *origins;

	gl_debug (DEBUG_PRINT, "START");

	merge = gl_label_get_merge (label);
	record_list = gl_merge_get_record_list (merge);

	pi = print_info_new (cr, label);
        frame = (lglTemplateFrame *)pi->template->frames->data;

	n_labels_per_page = lgl_template_frame_get_n_labels (frame);
	origins = lgl_template_frame_get_origins (frame);

        if (crop_marks_flag) {
                print_crop_marks (pi);
        }

        if (page == 0)
        {
                state->i_copy  = 0;
                state->p_record = (GList *)record_list;

                i_label = first - 1;
        }
        else
        {
                i_label = 0;
        }

	for (i_copy = state->i_copy; i_copy < n_copies; i_copy++) {

		for ( p=state->p_record; p!=NULL; p=p->next ) {
			record = (glMergeRecord *)p->data;

			if ( record->select_flag ) {

                                print_label (pi, label,
					     origins[i_label].x,
					     origins[i_label].y,
					     record,
					     outline_flag, reverse_flag);

				i_label++;
                                if (i_label == n_labels_per_page)
                                {
                                        g_free (origins);
                                        print_info_free (&pi);

                                        state->p_record = p->next;
                                        if (state->p_record == NULL)
                                        {
                                                state->p_record = (GList *)record_list;
                                                state->i_copy = i_copy + 1;
                                        }
                                        else
                                        {
                                                state->i_copy = i_copy;
                                        }
                                        return;
                                }
			}
		}
                state->p_record = (GList *)record_list;

	}

	g_free (origins);
	print_info_free (&pi);

	gl_debug (DEBUG_PRINT, "END");
}
