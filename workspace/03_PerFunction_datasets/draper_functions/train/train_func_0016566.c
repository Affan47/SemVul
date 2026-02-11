jpeg_build_huffman_index_baseline(j_decompress_ptr cinfo, huffman_index *index)
{
  if (cinfo->global_state == DSTATE_READY) {
    printf("Baseline Mode\n");

    transdecode_master_selection(cinfo);
    cinfo->global_state = DSTATE_RDCOEFS;
  }
  if (cinfo->global_state == DSTATE_RDCOEFS) {

    for (;;) {
      int retcode;

      if (cinfo->progress != NULL)
        (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);

      retcode = (*cinfo->inputctl->consume_input_build_huffman_index)
                    (cinfo, index, 0);
      if (retcode == JPEG_SUSPENDED)
        return FALSE;
      if (retcode == JPEG_REACHED_EOI)
        break;
      if (retcode == JPEG_SCAN_COMPLETED)
        break;


      if (cinfo->progress != NULL &&
	  (retcode == JPEG_ROW_COMPLETED || retcode == JPEG_REACHED_SOS)) {
        if (++cinfo->progress->pass_counter >= cinfo->progress->pass_limit) {

        cinfo->progress->pass_limit += (long) cinfo->total_iMCU_rows;
        }
      }
    }

    cinfo->global_state = DSTATE_STOPPING;
  }


  if ((cinfo->global_state == DSTATE_STOPPING ||
       cinfo->global_state == DSTATE_BUFIMAGE) && cinfo->buffered_image) {
    return TRUE;
  }

  ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  return FALSE;
}
