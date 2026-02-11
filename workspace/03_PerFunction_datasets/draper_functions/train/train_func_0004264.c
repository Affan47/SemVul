ModifyMountBonuses(char *mount, int min, int max, int hampered)
{
	MountType *pm = FindMount(mount);
	if (pm == NULL) return;
	if(min < 0) return;
	if(max < 0) return;
	if(hampered < min) return;
	pm->minBonus = min;
	pm->maxBonus = max;
	pm->maxHamperedBonus = hampered;
}
