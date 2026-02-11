auto_MACE_change_parm(FILE *fp, int index, int val)
{
    if (MACE_Parms[index].val != val) {
	fprintf(fp, "   dependent: assign(%s, %d).\n",
		MACE_Parms[index].name, val);

	MACE_Parms[index].val = val;
	MACE_dependent_parms(fp, index);
	}
}
