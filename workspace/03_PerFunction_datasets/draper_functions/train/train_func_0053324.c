omega_add_new_wild_card (omega_pb pb)
{
  int e;
  int i = ++pb->safe_vars;
  pb->num_vars++;


  if (pb->num_vars != i)
    {

      for (e = pb->num_geqs - 1; e >= 0; e--)
	{
	  if (pb->geqs[e].coef[i])
	    pb->geqs[e].touched = 1;

	  pb->geqs[e].coef[pb->num_vars] = pb->geqs[e].coef[i];
	}


      for (e = pb->num_eqs - 1; e >= 0; e--)
	pb->eqs[e].coef[pb->num_vars] = pb->eqs[e].coef[i];


      for (e = pb->num_subs - 1; e >= 0; e--)
	pb->subs[e].coef[pb->num_vars] = pb->subs[e].coef[i];


      pb->var[pb->num_vars] = pb->var[i];
    }


  for (e = pb->num_geqs - 1; e >= 0; e--)
    pb->geqs[e].coef[i] = 0;

  for (e = pb->num_eqs - 1; e >= 0; e--)
    pb->eqs[e].coef[i] = 0;

  for (e = pb->num_subs - 1; e >= 0; e--)
    pb->subs[e].coef[i] = 0;


  omega_name_wild_card (pb, i);
  return i;
}
