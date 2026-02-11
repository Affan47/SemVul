_is_same_pv(struct pv_match *pvmatch __attribute((unused)), struct pv_segment *pvseg, struct pv_area *pva)
{
	if (pvseg->pv != pva->map->pv)
		return 0;

	return 1;
}
