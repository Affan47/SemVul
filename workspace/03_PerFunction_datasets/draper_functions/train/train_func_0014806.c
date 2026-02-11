hostap_set_tim(local_info_t *local, int aid, int set)
{
	if (local->func->set_tim)
		local->func->set_tim(local->dev, aid, set);
}
