inc_timed(int idx, int v, bool notify)
{

	if ((idx < 0) || (idx > TMD_MAX)) return FALSE;


	if (idx == TMD_PARALYZED && p_ptr->timed[TMD_PARALYZED] > 0)
		return FALSE;


	v = v + p_ptr->timed[idx];

	return set_timed(idx, v, notify);
}
