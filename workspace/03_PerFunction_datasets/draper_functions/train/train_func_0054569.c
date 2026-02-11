WeightedHydrophobicity_ (double *min_valueP, double *max_valueP,
			     RuntimeS *runtimeSP)
{
int             residuesN, residueI;
int		used_residuesN;
static int	window_width = 11, half_window_width = 5;
static double	weightA[11] =  {+1.0, +1.0, +1.0, +1.0, +1.0,
				 0.0,
				-1.0, -1.0, -1.0, -1.0, -1.0};
int		windowI, combinedI;
double		hydrophobicity, weighted_hydrophobicity = 0;


residuesN = (int) runtimeSP->residuesN;
if (residuesN == 0) return -1;


*min_valueP = +999999.0;
*max_valueP = -999999.0;


for (residueI = 0; residueI < residuesN; residueI++)
	{

	used_residuesN = 0;


	weighted_hydrophobicity = 0.0;


	for (windowI = 0; windowI < window_width; windowI++)
		{

		combinedI = residueI - half_window_width + windowI;
		if (combinedI < 0) continue;
		if (combinedI >= residuesN) continue;


		hydrophobicity =
			(double) *(runtimeSP->hydrophobicityP + combinedI);


		weighted_hydrophobicity += hydrophobicity * weightA[windowI];


		used_residuesN++;
		}


	if (used_residuesN == window_width)
		{
		weighted_hydrophobicity /= (double) window_width;
		}
	else weighted_hydrophobicity = 0.0;


	*(runtimeSP->weighted_hydrophobicityP + residueI) =
						weighted_hydrophobicity;


	if (used_residuesN != window_width) continue;


	if (weighted_hydrophobicity < *min_valueP)
		{
		*min_valueP = weighted_hydrophobicity;
		}
	if (weighted_hydrophobicity > *max_valueP)
		{
		*max_valueP = weighted_hydrophobicity;
		}


	}


return 1;
}
