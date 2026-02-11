Angle_ (RuntimeS *runtimeSP, char *stringP)
{
char		*P;
int		n;
double		value;


P = stringP;
while ((n = *P++) != '\0')
	{
	if (!isdigit (n) && (n != '-') && (n != '.')) *(P - 1) = ' ';
	}


if (sscanf (stringP, "%lf", &value) != 1) return ERROR_ANGLE;


runtimeSP->helix_step_angle = value;


return COMMAND_ANGLE;
}
