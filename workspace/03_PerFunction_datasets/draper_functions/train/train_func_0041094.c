ft_lport_find_tpg(struct fc_lport *lport)
{
	struct ft_lport_wwn *ft_wwn;

	list_for_each_entry(ft_wwn, &ft_wwn_list, ft_wwn_node) {
		if (ft_wwn->wwpn == lport->wwpn)
			return ft_wwn->tpg;
	}
	return NULL;
}
