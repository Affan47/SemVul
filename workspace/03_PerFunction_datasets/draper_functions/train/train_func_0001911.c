encdesc_read_header(GtEncdesc *encdesc, FILE *fp)
{
  unsigned long cur_field_num;
  DescField *cur_field;

  encdesc_header_io_basics(encdesc, fp, encdesc_gt_xfread);

  encdesc->fields = gt_calloc((size_t) encdesc->num_of_fields,
                              sizeof (DescField));

  for (cur_field_num = 0;
       cur_field_num < encdesc->num_of_fields;
       cur_field_num++) {
    cur_field = &encdesc->fields[cur_field_num];
    cur_field->bits_per_num = 0;
    cur_field->prev_value = 0;
    io_field_sep_and_is_cons(cur_field, fp, encdesc_gt_xfread);

    if (cur_field->is_cons) {
      read_cons_field_header(cur_field, fp);
    }
    else {
      (void) gt_xfread(&cur_field->is_numeric, sizeof (bool), (size_t) 1, fp);
      if (cur_field->is_numeric) {
        read_numeric_field_header(cur_field, fp);
      }
      else {
        io_field_len_header(cur_field, fp, encdesc_gt_xfread);

        cur_field->bittab = gt_bittab_new(cur_field->len);

        cur_field->data = gt_calloc((size_t) (cur_field->len + 1),
                                    sizeof (char));
        (void) gt_xfread(cur_field->data, sizeof (char),
                         (size_t) cur_field->len, fp);

        read_field_header_bittab(cur_field, fp);

        cur_field->chars = gt_calloc((size_t) (cur_field->max_len + 1),
                                    sizeof (cur_field->chars));

        read_field_char_dists(cur_field, fp);
      }
    }
  }
}
