getval(syste, i, j, val, LINK)
int syste, i, j;
double *val;
struct LOC_getvect *LINK;
{
  locusvalues *WITH;
  phenotype *WITH1;

  WITH = thislocus[syste - 1];
  switch (WITH->which) {

  case quantitative:
    *val *= quanfun(LINK->p->phen[syste - 1], thislocus[syste - 1], i, j,
		    WITH->UU.U1.pm[i][j - 1], LINK);
    break;

  case affection:
    WITH1 = LINK->p->phen[syste - 1];
    *val *= WITH->UU.U0.pen[i][j - 1][WITH1->aff]
      [WITH1->liability - 1];
    break;

  case binary_:
  case null_:
  default:
    break;
  }
}
