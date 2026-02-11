vs_o_unsubscribe(VSNodeObject *node)
{
	unsigned int i;
	for(i = 0; i < node->group_count; i++)
		if(node->groups[i].name[0] != 0)
			vs_remove_subscriptor(node->groups[i].subscribers);
	vs_remove_subscriptor(node->trans_sub64);
	vs_remove_subscriptor(node->trans_sub32);
}
