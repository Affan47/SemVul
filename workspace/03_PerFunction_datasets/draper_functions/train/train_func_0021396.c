WalkablePassFilterCallback(colldet_filter * this, obstacle * obs, int obs_idx)
{
	if (get_obstacle_spec(obs->type)->flags & IS_WALKABLE)
		return TRUE;

	if (this->next)
		return (this->next->callback(this->next, obs, obs_idx));

	return FALSE;
}
