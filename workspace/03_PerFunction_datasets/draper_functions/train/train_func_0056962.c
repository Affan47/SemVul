scm_i_card_statistics (scm_t_cell *p, SCM hashtab, scm_t_heap_segment *seg)
{
  scm_t_c_bvec_long *bitvec = SCM_GC_CARD_BVEC(p);
  scm_t_cell * end = p + SCM_GC_CARD_N_CELLS;
  int span = seg->span;
  int offset = SCM_MAX (SCM_GC_CARD_N_HEADER_CELLS, span);

  if (!bitvec)

    return;

  for (p += offset; p < end; p += span, offset += span)
    {
      scm_t_bits tag = -1;
      SCM scmptr = PTR2SCM (p);

      if (!SCM_C_BVEC_GET (bitvec, offset))
        continue;

      tag = SCM_TYP7 (scmptr);
      if (tag == scm_tc7_smob || tag == scm_tc7_number)
	{


	  tag = SCM_TYP16(scmptr);
	}
      else
	switch (tag)
	{
	case scm_tcs_cons_imcar:
	  tag = scm_tc2_int;
	  break;
	case scm_tcs_cons_nimcar:
	  tag = scm_tc3_cons;
	  break;

	case scm_tcs_struct:
	  tag = scm_tc3_struct;
	  break;
	case scm_tcs_closures:
	  tag = scm_tc3_closure;
	  break;
	case scm_tcs_subrs:
	  tag = scm_tc7_asubr;
	  break;
	}

      {
        SCM handle = scm_hashq_create_handle_x (hashtab,
                                                scm_from_int (tag), SCM_INUM0);
        SCM_SETCDR (handle, scm_from_int (scm_to_int (SCM_CDR (handle)) + 1));
      }
    }
}
