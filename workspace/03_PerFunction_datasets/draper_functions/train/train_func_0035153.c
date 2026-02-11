emit_sos (j_compress_ptr cinfo)

{
  int i, td, ta;
  jpeg_component_info *compptr;

  emit_marker(cinfo, M_SOS);

  emit_2bytes(cinfo, 2 * cinfo->comps_in_scan + 2 + 1 + 3);

  emit_byte(cinfo, cinfo->comps_in_scan);

  for (i = 0; i < cinfo->comps_in_scan; i++) {
    compptr = cinfo->cur_comp_info[i];
    emit_byte(cinfo, compptr->component_id);
    td = compptr->dc_tbl_no;
    ta = compptr->ac_tbl_no;
    if (cinfo->process == JPROC_PROGRESSIVE) {


      if (cinfo->Ss == 0) {
	ta = 0;
	if (cinfo->Ah != 0 && !cinfo->arith_code)
	  td = 0;
      } else {
	td = 0;
      }
    }
    emit_byte(cinfo, (td << 4) + ta);
  }

  emit_byte(cinfo, cinfo->Ss);
  emit_byte(cinfo, cinfo->Se);
  emit_byte(cinfo, (cinfo->Ah << 4) + cinfo->Al);
}
