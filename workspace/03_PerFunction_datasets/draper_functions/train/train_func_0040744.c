atp_on_tool_add (GtkButton *button, gpointer user_data)
{
	ATPToolDialog *this = (ATPToolDialog *)user_data;
	ATPUserTool *tool;
	ATPToolEditor *ted;

	tool = get_current_tool (this);

	if (tool == NULL)
	{

		tool = atp_tool_list_append_new (atp_plugin_get_tool_list (this->plugin), NULL, ATP_TSTORE_LOCAL);
	}
	else
	{

		tool = atp_user_tool_append_new (tool, NULL, ATP_TSTORE_LOCAL);
	}

	ted = atp_tool_editor_new (tool, &this->tedl, this);
	atp_tool_editor_show (ted);
}
