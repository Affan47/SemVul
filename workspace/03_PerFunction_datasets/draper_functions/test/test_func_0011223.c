gnm_input_msg_new (char const *msg, char const *title)
{
	GnmInputMsg *res = g_object_new (GNM_INPUT_MSG_TYPE, NULL);

	if (msg != NULL)
		res->msg = go_string_new (msg);
	if (title != NULL)
		res->title = go_string_new (title);

	return res;
}
