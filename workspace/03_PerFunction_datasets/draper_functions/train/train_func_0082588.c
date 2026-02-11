write_scan_header (j_compress_ptr cinfo)
{
  my_marker_ptr marker = (my_marker_ptr) cinfo->marker;
  int i;
  jpeg_component_info *compptr;

  if (cinfo->arith_code) {


    emit_dac(cinfo);
  } else {


    for (i = 0; i < cinfo->comps_in_scan; i++) {
      compptr = cinfo->cur_comp_info[i];

      if (cinfo->Ss == 0 && cinfo->Ah == 0)
	emit_dht(cinfo, compptr->dc_tbl_no, FALSE);

      if (cinfo->Se)
	emit_dht(cinfo, compptr->ac_tbl_no, TRUE);
    }
  }


  if (cinfo->restart_interval != marker->last_restart_interval) {
    emit_dri(cinfo);
    marker->last_restart_interval = cinfo->restart_interval;
  }

  emit_sos(cinfo);
}
