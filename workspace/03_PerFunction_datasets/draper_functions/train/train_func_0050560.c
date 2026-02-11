vs_o_subscribe(VSNodeObject *node)
{
	unsigned int i;
	for(i = 0; i < node->link_count; i++)
	{
		const VSLink	*lnk = node->links + i;

		if(lnk->name[0] != 0)
		{
			verse_send_o_link_set(node->head.id, i, lnk->link, lnk->name, lnk->target_id);
			if(lnk->dimensions != 0)
			{
				verse_send_o_anim_run(node->head.id, i, lnk->time_s, lnk->time_f, lnk->dimensions,
						      lnk->pos, lnk->speed, lnk->accel,
						      lnk->scale, lnk->scale_speed);
			}
		}
	}
	if(node->light[0] != V_REAL64_MAX || node->light[1] != V_REAL64_MAX || node->light[2] != V_REAL64_MAX)
		verse_send_o_light_set(node->head.id, node->light[0], node->light[1], node->light[2]);
	for(i = 0; i < node->group_count; i++)
	{
		if(node->groups[i].name[0] != 0)
			verse_send_o_method_group_create(node->head.id, i, node->groups[i].name);
	}
	if(node->hidden)
		verse_send_o_hide(node->head.id, TRUE);
}
