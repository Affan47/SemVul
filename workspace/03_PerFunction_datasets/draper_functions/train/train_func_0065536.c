compute_sigma_contour_for_2_atts ( clsf_DS clsf, int clsf_class_number,
                                       int att_x, int att_y,
                                       int trans_att_x, int trans_att_y,
                                       int term_index_x, int term_index_y,
                                       float *mean_x, float *sigma_x,
                                       float *mean_y, float *sigma_y,
                                       float *rotation)
{
  int n_term_list;
  class_DS class = clsf->classes[clsf_class_number];
  model_DS model = clsf->classes[clsf_class_number]->model;
  term_DS *terms, term_x, term_y;
  i_real_DS i_real_struct = NULL;
  float **class_covar_x = NULL, **class_covar_y = NULL;
  float *term_list;
  float sigma_x_y, sum, diff, sigma_x_sq, sigma_y_sq, diff_sigma_x_y_term;
  float rotation_increment, arg;

  terms = model->terms;
  term_x = terms[term_index_x];
  term_y = terms[term_index_y];

  i_real_struct = (i_real_DS) class->i_values[trans_att_x];
  *mean_x = i_real_struct->mean_sigma_list[0];
  *sigma_x = i_real_struct->mean_sigma_list[1];
  class_covar_x = i_real_struct->class_covar;

  i_real_struct = (i_real_DS) class->i_values[trans_att_y];
  *mean_y = i_real_struct->mean_sigma_list[0];
  *sigma_y = i_real_struct->mean_sigma_list[1];
  class_covar_y = i_real_struct->class_covar;


  if (term_index_x == term_index_y) {


    term_list = i_real_struct->term_att_list;
    n_term_list = i_real_struct->n_term_att_list;
    sigma_x_y = get_sigma_x_y( trans_att_x, trans_att_y, class, n_term_list,
                               term_list, class_covar_x);
    sigma_x_sq = *sigma_x * *sigma_x;
    sigma_y_sq = *sigma_y * *sigma_y;
    sum = sigma_x_sq + sigma_y_sq;
    diff = sigma_x_sq - sigma_y_sq;


    if (*sigma_y > *sigma_x) {
      *rotation = 0.5 *  (float) M_PI;
    } else {
      *rotation = 0.0;
    }
    diff_sigma_x_y_term = sqrt( (diff * diff) +
                                          ( 4.0 * sigma_x_y * sigma_x_y));
    *sigma_x = sqrt( 0.5 * ( sum + diff_sigma_x_y_term));
    *sigma_y = sqrt( 0.5 * ( sum - diff_sigma_x_y_term));
    if (percent_equal( diff, 0.0, SINGLE_FLOAT_EPSILON) == TRUE) {
      rotation_increment = ( (float) M_PI) / 4.0;
    } else {
      arg = ( 2.0 * sigma_x_y ) / diff;
      rotation_increment = (float) (0.5 * atan( (double) arg));
    }
    *rotation = *rotation + rotation_increment;
  } else {


    *rotation = 0.0;
  }
  return(1);
}
