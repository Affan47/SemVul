collect_zipstats(void *unused)
{
	rb_dlink_node *ptr;
	struct Client *target_p;
	char buf[sizeof(uint8_t) + sizeof(int32_t) + HOSTLEN];
	void *odata;
	size_t len;
	int32_t id;

	buf[0] = 'S';
	odata = buf + sizeof(uint8_t) + sizeof(int32_t);

	RB_DLINK_FOREACH(ptr, serv_list.head)
	{
		target_p = ptr->data;
		if(IsCapable(target_p, CAP_ZIP))
		{
			len = sizeof(uint8_t) + sizeof(uint32_t);

			id = rb_get_fd(target_p->localClient->F);
			int32_to_buf(&buf[1], rb_get_fd(target_p->localClient->F));
			rb_strlcpy(odata, target_p->name, (sizeof(buf) - len));
			len += strlen(odata) + 1;
			ssl_cmd_write_queue(target_p->localClient->z_ctl, NULL, 0, buf, len);
		}
	}
}
