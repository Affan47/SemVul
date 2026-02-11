omega_count_red_equations (omega_pb pb)
{
  int e, i;
  int result = 0;

  for (e = 0; e < pb->num_eqs; e++)
    if (pb->eqs[e].color == omega_red)
      {
	for (i = pb->num_vars; i > 0; i--)
	  if (pb->geqs[e].coef[i])
	    break;

	if (i == 0 && pb->geqs[e].coef[0] == 1)
	  return 0;
	else
	  result += 2;
      }

  for (e = 0; e < pb->num_geqs; e++)
    if (pb->geqs[e].color == omega_red)
      result += 1;

  for (e = 0; e < pb->num_subs; e++)
    if (pb->subs[e].color == omega_red)
      result += 2;

  return result;
}
