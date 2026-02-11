team_nl_send_port_list_get(struct team *team, u32 portid, u32 seq,
				      int flags, team_nl_send_func_t *send_func,
				      struct team_port *one_port)
{
	struct nlattr *port_list;
	struct nlmsghdr *nlh;
	void *hdr;
	struct team_port *port;
	int err;
	struct sk_buff *skb = NULL;
	bool incomplete;
	int i;

	port = list_first_entry_or_null(&team->port_list,
					struct team_port, list);

start_again:
	err = __send_and_alloc_skb(&skb, team, portid, send_func);
	if (err)
		return err;

	hdr = genlmsg_put(skb, portid, seq, &team_nl_family, flags | NLM_F_MULTI,
			  TEAM_CMD_PORT_LIST_GET);
	if (!hdr) {
		nlmsg_free(skb);
		return -EMSGSIZE;
	}

	if (nla_put_u32(skb, TEAM_ATTR_TEAM_IFINDEX, team->dev->ifindex))
		goto nla_put_failure;
	port_list = nla_nest_start(skb, TEAM_ATTR_LIST_PORT);
	if (!port_list)
		goto nla_put_failure;

	i = 0;
	incomplete = false;


	if (one_port) {
		err = team_nl_fill_one_port_get(skb, one_port);
		if (err)
			goto errout;
	} else if (port) {
		list_for_each_entry_from(port, &team->port_list, list) {
			err = team_nl_fill_one_port_get(skb, port);
			if (err) {
				if (err == -EMSGSIZE) {
					if (!i)
						goto errout;
					incomplete = true;
					break;
				}
				goto errout;
			}
			i++;
		}
	}

	nla_nest_end(skb, port_list);
	genlmsg_end(skb, hdr);
	if (incomplete)
		goto start_again;

send_done:
	nlh = nlmsg_put(skb, portid, seq, NLMSG_DONE, 0, flags | NLM_F_MULTI);
	if (!nlh) {
		err = __send_and_alloc_skb(&skb, team, portid, send_func);
		if (err)
			goto errout;
		goto send_done;
	}

	return send_func(skb, team, portid);

nla_put_failure:
	err = -EMSGSIZE;
errout:
	genlmsg_cancel(skb, hdr);
	nlmsg_free(skb);
	return err;
}
