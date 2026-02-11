png_row_callback   (png_structp png_read_ptr,
                    png_bytep   new_row,
                    png_uint_32 row_num,
                    int pass_num)
{
        LoadContext* lc;
        guchar* old_row = NULL;

        lc = png_get_progressive_ptr(png_read_ptr);

        if (lc->fatal_error_occurred)
                return;

        if (row_num >= lc->pixbuf->height) {
                lc->fatal_error_occurred = TRUE;
                if (lc->error && *lc->error == NULL) {
                        g_set_error_literal (lc->error,
                                             GDK_PIXBUF_ERROR,
                                             GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                             _("Fatal error reading PNG image file"));
                }
                return;
        }

        if (lc->first_row_seen_in_chunk < 0) {
                lc->first_row_seen_in_chunk = row_num;
                lc->first_pass_seen_in_chunk = pass_num;
        }

        lc->max_row_seen_in_chunk = MAX(lc->max_row_seen_in_chunk, ((gint)row_num));
        lc->last_row_seen_in_chunk = row_num;
        lc->last_pass_seen_in_chunk = pass_num;

        old_row = lc->pixbuf->pixels + (row_num * lc->pixbuf->rowstride);

        png_progressive_combine_row(lc->png_read_ptr, old_row, new_row);
}
