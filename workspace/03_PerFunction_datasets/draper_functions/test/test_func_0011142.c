ModifyItemProductionOutput(int it, int months, int count)
{
	if(it < 0 || it > (NITEMS-1)) return;
	if(count < 0) count = 0;
	if(months < 0) months = 0;
	ItemDefs[it].pMonths = months;
	ItemDefs[it].pOut = count;
}
