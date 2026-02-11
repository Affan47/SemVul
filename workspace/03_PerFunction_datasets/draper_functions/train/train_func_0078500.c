free_class_DS( class_DS class, char *type, clsf_DS clsf, int n_class)
{
  int n_tparm, n_att;
  tparm_DS tparm;
  char *att_type;
  i_discrete_DS i_discrete_struct;
  i_real_DS i_real_struct;

  if (G_clsf_storage_log_p == TRUE)
    fprintf(stdout, "free_class(%s): %p\n", type, (void *) class);
  G_n_freed_classes++;

  for (n_tparm=0; n_tparm < class->num_tparms ; n_tparm++) {
    tparm = class->tparms[n_tparm];
    free_tparm_DS( tparm);
  }
  free( class->tparms);

  if (class->i_values != NULL) {
    for (n_att=0; n_att<clsf->database->n_atts; n_att++) {
      att_type = report_att_type( clsf, n_class, n_att);
      if (eqstring( att_type, "discrete") == TRUE) {
        i_discrete_struct = (i_discrete_DS) class->i_values[n_att];
        free( i_discrete_struct->p_p_star_list);
        free( i_discrete_struct);
      }
      if (eqstring( att_type, "integer") == TRUE) {
        fprintf( stderr, "att_type integer not supported\n");
        abort();
      }
      if (eqstring( att_type, "real") == TRUE) {
        i_real_struct = (i_real_DS) class->i_values[n_att];
        free( i_real_struct->mean_sigma_list);
        free( i_real_struct);

      }
    }
    free( class->i_values);
  }


  if (class->wts != NULL)
    free( class->wts);

  free( class);
}
