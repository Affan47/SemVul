attribute_model_term_number( int n_att, model_DS model)
{
  int i, j;

  for (i=0; i<model->n_terms; i++) {
    for (j=0; j<model->terms[i]->n_atts; j++)
      if (model->terms[i]->att_list[j] == ((float) n_att))
        goto out;
  }
 out: return (i);
}
