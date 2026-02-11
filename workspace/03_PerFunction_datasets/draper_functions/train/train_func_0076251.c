loadPaulingENeg (double **values, int *len)
{
	*values = new double[MAX_ELT];
	GcuElectronegativity en;
	en.scale = "Pauling";
	for (int i = 1; i <= MAX_ELT; i++) {
		en.Z = i;
		(*values)[i - 1] = (gcu_element_get_electronegativity (&en))?
							en.value.value: go_nan;
	}
	*len = MAX_ELT;
}
