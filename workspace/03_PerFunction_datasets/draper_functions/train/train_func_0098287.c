input_conn_new(struct input_device *idev,
					const char *uuid, int timeout)
{
	struct input_conn *iconn;

	iconn = g_new0(struct input_conn, 1);
	iconn->timeout = timeout;
	iconn->uuid = g_strdup(uuid);
	iconn->idev = idev;

	return iconn;
}
