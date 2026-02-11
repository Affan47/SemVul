pre_process_data (j_compress_ptr cinfo,
		  JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
		  JDIMENSION in_rows_avail,
		  JSAMPIMAGE output_buf, JDIMENSION *out_row_group_ctr,
		  JDIMENSION out_row_groups_avail)
{
  my_prep_ptr prep = (my_prep_ptr) cinfo->prep;
  int numrows, ci;
  JDIMENSION inrows;
  jpeg_component_info * compptr;

  while (*in_row_ctr < in_rows_avail &&
	 *out_row_group_ctr < out_row_groups_avail) {

    inrows = in_rows_avail - *in_row_ctr;
    numrows = cinfo->max_v_samp_factor - prep->next_buf_row;
    numrows = (int) MIN((JDIMENSION) numrows, inrows);
    (*cinfo->cconvert->color_convert) (cinfo, input_buf + *in_row_ctr,
				       prep->color_buf,
				       (JDIMENSION) prep->next_buf_row,
				       numrows);
    *in_row_ctr += numrows;
    prep->next_buf_row += numrows;
    prep->rows_to_go -= numrows;

    if (prep->rows_to_go == 0 &&
	prep->next_buf_row < cinfo->max_v_samp_factor) {
      for (ci = 0; ci < cinfo->num_components; ci++) {
	expand_bottom_edge(prep->color_buf[ci], cinfo->image_width,
			   prep->next_buf_row, cinfo->max_v_samp_factor);
      }
      prep->next_buf_row = cinfo->max_v_samp_factor;
    }

    if (prep->next_buf_row == cinfo->max_v_samp_factor) {
      (*cinfo->downsample->downsample) (cinfo,
					prep->color_buf, (JDIMENSION) 0,
					output_buf, *out_row_group_ctr);
      prep->next_buf_row = 0;
      (*out_row_group_ctr)++;
    }


    if (prep->rows_to_go == 0 &&
	*out_row_group_ctr < out_row_groups_avail) {
      for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	   ci++, compptr++) {
	expand_bottom_edge(output_buf[ci],
			   compptr->width_in_blocks * DCTSIZE,
			   (int) (*out_row_group_ctr * compptr->v_samp_factor),
			   (int) (out_row_groups_avail * compptr->v_samp_factor));
      }
      *out_row_group_ctr = out_row_groups_avail;
      break;
    }
  }
}
