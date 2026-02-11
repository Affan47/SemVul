remote_editor_set_property (GObject      *object,
		    guint         param_id,
		    const GValue *value,
		    GParamSpec   *pspec)
{
	GiggleRemote           *remote;

	switch (param_id) {
	case PROP_REMOTE:
		remote = g_value_get_object (value);
		if(!remote) {
			GiggleRemoteBranch* branch;
			remote = giggle_remote_new (_("Unnamed"));
			branch = giggle_remote_branch_new (GIGGLE_REMOTE_DIRECTION_PULL,
							   "ref/heads/master:ref/heads/incoming");
			giggle_remote_add_branch (remote, branch);
			g_object_unref (branch);
		}
		remote_editor_set_remote (GIGGLE_REMOTE_EDITOR (object),
					  remote);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}
