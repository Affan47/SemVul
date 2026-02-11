xline_expire(void *arg)
{
	xline_t *x;
	mowgli_node_t *n, *tn;

	MOWGLI_ITER_FOREACH_SAFE(n, tn, xlnlist.head)
	{
		x = (xline_t *)n->data;

		if (x->duration == 0)
			continue;

		if (x->expires <= CURRTIME)
		{
			slog(LG_INFO, _("XLINE:EXPIRE: \2%s\2 set \2%s\2 ago by \2%s\2"),
				x->realname, time_ago(x->settime), x->setby);

			verbose_wallops(_("XLINE expired on \2%s\2, set by \2%s\2"),
				x->realname, x->setby);

			xline_delete(x->realname);
		}
	}
}
