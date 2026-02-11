namedmutex_details (struct _WapiHandleShared *handle)
{
	static gchar buf[80];
	gchar *name;
	struct _WapiHandle_namedmutex *mut=&handle->u.namedmutex;

	name = mut->sharedns.name;

	g_snprintf (buf, sizeof(buf), "[%15s] own: %5d:%5ld, count: %5u",
		    name==NULL?(gchar *)"":name, mut->pid, mut->tid,
		    mut->recursion);

	return(buf);
}
