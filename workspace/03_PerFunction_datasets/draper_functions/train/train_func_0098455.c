fso_gsm_at_command_sequence_append (FsoGsmAtCommandSequence* self, gchar** commands, int commands_length1) {
	gchar** _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = commands;
	_tmp0__length1 = commands_length1;
	{
		gchar** cmd_collection = NULL;
		gint cmd_collection_length1 = 0;
		gint _cmd_collection_size_ = 0;
		gint cmd_it = 0;
		cmd_collection = _tmp0_;
		cmd_collection_length1 = _tmp0__length1;
		for (cmd_it = 0; cmd_it < _tmp0__length1; cmd_it = cmd_it + 1) {
			gchar* _tmp1_ = NULL;
			gchar* cmd = NULL;
			_tmp1_ = g_strdup (cmd_collection[cmd_it]);
			cmd = _tmp1_;
			{
				gchar** _tmp2_ = NULL;
				gint _tmp2__length1 = 0;
				const gchar* _tmp3_ = NULL;
				gchar* _tmp4_ = NULL;
				_tmp2_ = self->priv->commands;
				_tmp2__length1 = self->priv->commands_length1;
				_tmp3_ = cmd;
				_tmp4_ = g_strdup (_tmp3_);
				_vala_array_add7 (&self->priv->commands, &self->priv->commands_length1, &self->priv->_commands_size_, _tmp4_);
				_g_free0 (cmd);
			}
		}
	}
}
