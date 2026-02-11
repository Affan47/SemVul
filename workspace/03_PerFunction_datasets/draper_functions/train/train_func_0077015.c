memory_get_stat(
  vsignal*      sig,
  unsigned int* wr_hit,
  unsigned int* rd_hit,
  unsigned int* ae_total,
  unsigned int* tog01_hit,
  unsigned int* tog10_hit,
  unsigned int* tog_total,
  unsigned int* excluded,
  bool*         cov_found,
  bool          ignore_excl
) { PROFILE(MEMORY_GET_STAT);

  unsigned int i;
  unsigned int pwidth;
  bool         ae_cov_found  = TRUE;
  bool         tog_cov_found = FALSE;


  pwidth = 1;
  for( i=(sig->udim_num); i<(sig->udim_num + sig->pdim_num); i++ ) {
    if( sig->dim[i].msb > sig->dim[i].lsb ) {
      pwidth *= (sig->dim[i].msb - sig->dim[i].lsb) + 1;
    } else {
      pwidth *= (sig->dim[i].lsb - sig->dim[i].msb) + 1;
    }
  }


  for( i=0; i<sig->value->width; i+=pwidth ) {
    if( (sig->suppl.part.excluded == 1) && !ignore_excl ) {
      (*wr_hit)++;
      (*rd_hit)++;
      *excluded += 2;
    } else {
      unsigned int wr = 0;
      unsigned int rd = 0;
      vector_mem_rw_count( sig->value, (int)i, (int)((i + pwidth) - 1), &wr, &rd );
      if( wr > 0 ) {
        (*wr_hit)++;
      }
      if( rd > 0 ) {
        (*rd_hit)++;
      }
      ae_cov_found &= (wr > 0) && (rd > 0);
    }
    (*ae_total)++;
  }


  *tog_total += sig->value->width;
  if( (sig->suppl.part.excluded == 1) && !ignore_excl ) {
    *tog01_hit += sig->value->width;
    *tog10_hit += sig->value->width;
    *excluded  += (sig->value->width * 2);
  } else {
    unsigned int hit01 = 0;
    unsigned int hit10 = 0;
    vector_toggle_count( sig->value, &hit01, &hit10 );
    *tog01_hit += hit01;
    *tog10_hit += hit10;
    tog_cov_found = (hit01 == sig->value->width) && (hit10 == sig->value->width);
  }

  *cov_found |= ae_cov_found && tog_cov_found;

  PROFILE_END;

}
