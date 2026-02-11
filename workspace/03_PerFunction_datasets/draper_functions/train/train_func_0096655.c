find_reqid(child_cfg_t *child_cfg)
{
	enumerator_t *enumerator, *children;
	child_sa_t *child_sa;
	ike_sa_t *ike_sa;
	char *name;
	u_int32_t reqid;

	reqid = charon->traps->find_reqid(charon->traps, child_cfg);
	if (reqid)
	{
		return reqid;
	}

	name = child_cfg->get_name(child_cfg);
	enumerator = charon->controller->create_ike_sa_enumerator(
													charon->controller, TRUE);
	while (enumerator->enumerate(enumerator, &ike_sa))
	{
		children = ike_sa->create_child_sa_enumerator(ike_sa);
		while (children->enumerate(children, (void**)&child_sa))
		{
			if (streq(name, child_sa->get_name(child_sa)))
			{
				reqid = child_sa->get_reqid(child_sa);
				break;
			}
		}
		children->destroy(children);
		if (reqid)
		{
			break;
		}
	}
	enumerator->destroy(enumerator);
	return reqid;
}
