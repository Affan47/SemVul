update_m_approx_fn( class_DS class)
{
  int i,num;
  float w_j = class->w_j;
  double sum = 0.0;

  tparm_DS tparm;

  if (class->known_parms_p == TRUE)
    class->log_a_w_s_h_j = class->log_a_w_s_h_pi_theta;
  else if (w_j <= 1.0)
    fprintf(stderr,
            "update_m_approx-fn called with w_j = %f, log_a_w_s_h_j not updated.\n",
            w_j);
  else {
    num = class->model->n_terms;
    for (i=0; i<num; i++) {
      tparm=class->tparms[i];
      tparm->w_j = w_j;

      switch(tparm->tppt) {
      case  MN_CN:
        sum += multi_normal_cn_update_m_approx(tparm);
        break;
      case  SM:
        sum += single_multinomial_update_m_approx(tparm);
        break;
      case  SN_CM:
        sum += single_normal_cm_update_m_approx(tparm);
        break;
      case  SN_CN:
        sum += single_normal_cn_update_m_approx(tparm);
        break;

      case MM_D:
      case MM_S:
      default:
        fprintf(stderr, "ERROR: unknown type in update_m_approx; parm=%d, type=%d",
                i, tparm->tppt);
        abort();
      }
    }


    class->log_a_w_s_h_j = sum;
  }
  return (class->log_a_w_s_h_j);
}
