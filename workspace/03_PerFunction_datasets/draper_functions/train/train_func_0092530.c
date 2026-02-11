fso_gsm_abstract_modem_registerAtCommands (FsoGsmAbstractModem* self) {
	GeeHashMap* _tmp0_ = NULL;
	GeeHashMap* _tmp1_ = NULL;
	GeeHashMap* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, FSO_GSM_TYPE_AT_COMMAND, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL, NULL, NULL);
	_g_object_unref0 (self->commands);
	self->commands = _tmp0_;
	_tmp1_ = self->commands;
	fso_gsm_registerGenericAtCommands (_tmp1_);
	_tmp2_ = self->commands;
	fso_gsm_abstract_modem_registerCustomAtCommands (self, _tmp2_);
	{
		GeeIterator* _command_it = NULL;
		GeeHashMap* _tmp3_ = NULL;
		GeeCollection* _tmp4_ = NULL;
		GeeCollection* _tmp5_ = NULL;
		GeeCollection* _tmp6_ = NULL;
		GeeIterator* _tmp7_ = NULL;
		GeeIterator* _tmp8_ = NULL;
		_tmp3_ = self->commands;
		_tmp4_ = gee_abstract_map_get_values ((GeeMap*) _tmp3_);
		_tmp5_ = _tmp4_;
		_tmp6_ = _tmp5_;
		_tmp7_ = gee_iterable_iterator ((GeeIterable*) _tmp6_);
		_tmp8_ = _tmp7_;
		_g_object_unref0 (_tmp6_);
		_command_it = _tmp8_;
		while (TRUE) {
			GeeIterator* _tmp9_ = NULL;
			gboolean _tmp10_ = FALSE;
			FsoGsmAtCommand* command = NULL;
			GeeIterator* _tmp11_ = NULL;
			gpointer _tmp12_ = NULL;
			FsoGsmAbstractAtCommand* cmd = NULL;
			FsoGsmAtCommand* _tmp13_ = NULL;
			FsoGsmAbstractAtCommand* _tmp14_ = NULL;
			FsoGsmAbstractAtCommand* _tmp15_ = NULL;
			_tmp9_ = _command_it;
			_tmp10_ = gee_iterator_next (_tmp9_);
			if (!_tmp10_) {
				break;
			}
			_tmp11_ = _command_it;
			_tmp12_ = gee_iterator_get (_tmp11_);
			command = (FsoGsmAtCommand*) _tmp12_;
			_tmp13_ = command;
			_tmp14_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp13_, FSO_GSM_TYPE_ABSTRACT_AT_COMMAND) ? ((FsoGsmAbstractAtCommand*) _tmp13_) : NULL);
			cmd = _tmp14_;
			_tmp15_ = cmd;
			if (_tmp15_ != NULL) {
				FsoGsmAbstractAtCommand* _tmp16_ = NULL;
				_tmp16_ = cmd;
				fso_gsm_abstract_at_command_assign_modem (_tmp16_, (FsoGsmModem*) self);
			}
			_g_object_unref0 (cmd);
			_g_object_unref0 (command);
		}
		_g_object_unref0 (_command_it);
	}
}
