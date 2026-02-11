ansitextview_append_formatted(GtkTextBuffer  *buffer,
                              GtkTextIter    *iter,
                              const gchar    *text,
                              gsize           len,
                              TextAppearance *ta,
                              GtkTextTag     *extra_tag)
{
  gint        start_offset;
  GtkTextIter start_iter;
  gint        fg_color_idx;
  gint        bg_color_idx;

  start_offset = gtk_text_iter_get_offset(iter);

  gtk_text_buffer_insert(buffer,
                         iter,
                         text,
                         len);

  gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, start_offset);


  fg_color_idx = ta->state.fg_base_idx + ta->state.fg_color;
  bg_color_idx = ta->state.bg_base_idx + ta->state.bg_color;

  if (ta->state.foreground_color_tag) {
    gtk_text_buffer_apply_tag(buffer,
                              ta->state.foreground_color_tag,
                              &start_iter,
                              iter);
  } else {
    gint idx_to_use;

    if (ta->state.reverse ^ ta->state.hidden) {
      if (bg_color_idx == ANSI_DEFAULT_COLOR_IDX) {
        idx_to_use = ANSI_REVERSE_DEFAULT_IDX;
      } else if (bg_color_idx == ANSI_DEFAULT_BOLD_COLOR_IDX) {
        idx_to_use = ANSI_REVERSE_BOLD_DEFAULT_IDX;
      } else {
        idx_to_use = bg_color_idx;
      }
    } else {
      idx_to_use = fg_color_idx;
    }
    gtk_text_buffer_apply_tag(buffer,
                              ta->ansi_fore_tags[idx_to_use],
                              &start_iter,
                              iter);
  }

  if (ta->state.background_color_tag) {
    gtk_text_buffer_apply_tag(buffer,
                              ta->state.background_color_tag,
                              &start_iter,
                              iter);
  } else {
    gint idx_to_use;

    if (!ta->state.reverse) {
      idx_to_use = bg_color_idx;
    } else {
      if (fg_color_idx == ANSI_DEFAULT_COLOR_IDX) {
        idx_to_use = ANSI_REVERSE_DEFAULT_IDX;
      } else if (fg_color_idx == ANSI_DEFAULT_BOLD_COLOR_IDX) {
        idx_to_use = ANSI_REVERSE_BOLD_DEFAULT_IDX;
      } else {
        idx_to_use = fg_color_idx;
      }
    }
    gtk_text_buffer_apply_tag(buffer,
                              ta->ansi_back_tags[idx_to_use],
                              &start_iter,
                              iter);
  }


  if (ta->state.underline == PANGO_UNDERLINE_SINGLE) {
    gtk_text_buffer_apply_tag(buffer, ta->underline_tag, &start_iter, iter);
  } else if (ta->state.underline == PANGO_UNDERLINE_DOUBLE) {
    gtk_text_buffer_apply_tag(buffer, ta->dblunderline_tag, &start_iter, iter);
  }
  if (ta->state.strike) {
    gtk_text_buffer_apply_tag(buffer, ta->strike_tag, &start_iter, iter);
  }
  if (ta->state.italics) {
    gtk_text_buffer_apply_tag(buffer, ta->italics_tag, &start_iter, iter);
  }


  if (extra_tag) {
    gtk_text_buffer_apply_tag(buffer, extra_tag, &start_iter, iter);
  }
}
