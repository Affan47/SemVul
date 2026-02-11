log_likelihood_fn( float *datum, class_DS class, double limit)
{
  int i = 0, num;
  float sum = 0.0;
  tparm_DS tparm;

  num = class->num_tparms;
  do {
    tparm=class->tparms[i];
    tparm->datum=datum;

    switch(tparm->tppt) {
    case  MN_CN:
      sum += (float) multi_normal_cn_log_likelihood(tparm);
      break;
    case  SM:
      sum += (float) single_multinomial_log_likelihood(tparm);
      break;
    case  SN_CM:
      sum += (float) single_normal_cm_log_likelihood(tparm);
      break;
    case  SN_CN:
      sum += (float) single_normal_cn_log_likelihood(tparm);
      break;

    case MM_D:
    case MM_S:
    default:
      fprintf(stderr, "ERROR: unknown type in log_likelihood; parm=%d, type= %d",
              i, tparm->tppt);
      abort();
    }

  } while ((++i < num) && (sum >= (float) limit));


  return (class->log_pi_j + sum);
}
