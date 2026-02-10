gck_session_get_info (GckSession *self)
{
	GckSessionInfo *sessioninfo;
	CK_FUNCTION_LIST_PTR funcs;
	CK_SESSION_INFO info;
	GckModule *module;
	CK_RV rv;

	g_return_val_if_fail (GCK_IS_SESSION (self), NULL);

	module = gck_session_get_module (self);
	g_return_val_if_fail (GCK_IS_MODULE (module), NULL);

	funcs = gck_module_get_functions (module);
	g_return_val_if_fail (funcs, NULL);

	memset (&info, 0, sizeof (info));
	rv = (funcs->C_GetSessionInfo) (self->pv->handle, &info);

	g_object_unref (module);

	if (rv != CKR_OK) {
		g_warning ("couldn't get session info: %s", gck_message_from_rv (rv));
		return NULL;
	}

	sessioninfo = g_new0 (GckSessionInfo, 1);
	sessioninfo->flags = info.flags;
	sessioninfo->slot_id = info.slotID;
	sessioninfo->state = info.state;
	sessioninfo->device_error = info.ulDeviceError;

	return sessioninfo;
}
