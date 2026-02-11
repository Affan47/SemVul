write_tparm_DS( tparm_DS term_param, int parm_num, FILE *stream)

{
  char caller[] = "write_tparm_DS";

  safe_fprintf(stream, caller, "tparm_DS %d\n", parm_num);
  safe_fprintf(stream, caller, "n_atts, tppt(type)\n");
  safe_fprintf(stream, caller, "%d %d ", term_param->n_atts, term_param->tppt);

  switch(term_param->tppt) {
  case  SM:
    write_sm_params( &(term_param->ptype.sm), term_param->n_atts, stream);
    break;
  case  SN_CM:
    write_sn_cm_params( &(term_param->ptype.sn_cm), stream);
    break;
  case  SN_CN:
    write_sn_cn_params( &(term_param->ptype.sn_cn), stream);
    break;
  case MM_D:
    write_mm_d_params( &(term_param->ptype.mm_d), term_param->n_atts, stream);
    break;
  case MM_S:
    write_mm_s_params( &(term_param->ptype.mm_s), term_param->n_atts, stream);
    break;
  case MN_CN:
    write_mn_cn_params( &(term_param->ptype.mn_cn), term_param->n_atts, stream);
    break;
  default:
    printf("\n write_tparms_DS: unknown type of enum MODEL_TYPES=%d\n",
           term_param->tppt);
    abort();
  }

  safe_fprintf(stream, caller, "n_term, n_att, n_att_indices, n_datum, n_data\n");
  safe_fprintf(stream, caller, "%d %d %d %d %d\n", term_param->n_term,
          term_param->n_att, term_param->n_att_indices, term_param->n_datum,
          term_param->n_data);
  safe_fprintf(stream, caller, "w_j, ranges, class_wt, disc_scale\n");
  safe_fprintf(stream, caller, "%.7e %.7e %.7e %.7e\n", term_param->w_j, term_param->ranges,
          term_param->class_wt, term_param->disc_scale);
  safe_fprintf(stream, caller, "log_pi, log_att_delta, log_delta, wt_m, log_marginal\n");
  safe_fprintf(stream, caller, "%.7e %.7e %.7e %.7e %.7e\n", term_param->log_pi,
          term_param->log_att_delta, term_param->log_delta, term_param->wt_m,
          term_param->log_marginal);


}
