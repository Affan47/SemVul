transpose_critical_parameters (j_compress_ptr dstinfo)
{
  int tblno, i, j, ci, itemp;
  jpeg_component_info *compptr;
  JQUANT_TBL *qtblptr;
  JDIMENSION dtemp;
  UINT16 qtemp;


  dtemp = dstinfo->image_width;
  dstinfo->image_width = dstinfo->image_height;
  dstinfo->image_height = dtemp;


  for (ci = 0; ci < dstinfo->num_components; ci++) {
    compptr = dstinfo->comp_info + ci;
    itemp = compptr->h_samp_factor;
    compptr->h_samp_factor = compptr->v_samp_factor;
    compptr->v_samp_factor = itemp;
  }


  for (tblno = 0; tblno < NUM_QUANT_TBLS; tblno++) {
    qtblptr = dstinfo->quant_tbl_ptrs[tblno];
    if (qtblptr != NULL) {
      for (i = 0; i < DCTSIZE; i++) {
	for (j = 0; j < i; j++) {
	  qtemp = qtblptr->quantval[i*DCTSIZE+j];
	  qtblptr->quantval[i*DCTSIZE+j] = qtblptr->quantval[j*DCTSIZE+i];
	  qtblptr->quantval[j*DCTSIZE+i] = qtemp;
	}
      }
    }
  }
}
