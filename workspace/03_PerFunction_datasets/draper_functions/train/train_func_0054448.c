set_ignore_att_info( model_DS model, database_DS d_base)
{
  int i;
  shortstr *locs = model->att_locs, *att_ignore_ids = model->att_ignore_ids;

  for (i=0; i<model->n_att_locs; i++)
    if (eqstring(locs[i], "") == TRUE) {
      strcpy(locs[i], "ignore");
      if (find_str_in_table(d_base->att_info[i]->sub_type, G_transforms,
                            NUM_TRANSFORMS) >= 0)
        strcpy(att_ignore_ids[i], "transformed-attribute-ignored");
      else if (eqstring( d_base->att_info[i]->warnings_and_errors->unspecified_dummy_warning,
                        "") == FALSE)
        strcpy(att_ignore_ids[i], "att_type_not_specified");
      else if (eqstring(d_base->att_info[i]->type, "dummy") == TRUE)
        strcpy(att_ignore_ids[i], "att_type_is_dummy");
      else
        strcpy(att_ignore_ids[i], "model_term_not_specified");
    }


}
