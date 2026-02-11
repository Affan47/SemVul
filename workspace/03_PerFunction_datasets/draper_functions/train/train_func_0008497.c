cyapa_is_pip_bl_mode(struct cyapa *cyapa)
{
	if (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_BL)
		return true;

	if (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_BL)
		return true;

	return false;
}
