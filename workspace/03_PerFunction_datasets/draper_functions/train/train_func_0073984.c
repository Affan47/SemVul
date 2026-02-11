ExtractSlabSteps_ (ConfigS *configSP, char *sP)
{
char		*P0, *P1;
int		n;
double		d1, d2, d3, d4, d5;


if ((P0 = strstr (sP, ":")) == NULL) P0 = sP;


P1 = P0;
while ((n = *P1++) != '\0')
	{
	if (!isdigit (n) && (n != '-') && (n != '.')) *(P1 - 1) = ' ';
	}


if (sscanf (P0, "%lf %lf %lf %lf %lf", &d1, &d2, &d3, &d4, &d5) != 5)
	{
	return -1;
	}


configSP->slab_stepA[0] = d1;
configSP->slab_stepA[1] = d2;
configSP->slab_stepA[2] = d3;
configSP->slab_stepA[3] = d4;
configSP->slab_stepA[4] = d5;


return 1;
}
