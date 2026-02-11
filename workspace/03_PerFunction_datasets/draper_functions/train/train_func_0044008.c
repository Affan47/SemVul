atCommandFactory (const gchar* command) {
	FsoGsmAtCommand* result = NULL;
	GeeHashMap* _tmp0_ = NULL;
	FsoGsmAtCommand* cmd = NULL;
	GeeHashMap* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gpointer _tmp3_ = NULL;
#line 33 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	g_return_val_if_fail (command != NULL, NULL);
#line 35 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_tmp0_ = commands;
#line 35 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_vala_assert (_tmp0_ != NULL, "commands != null");
#line 36 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_tmp1_ = commands;
#line 36 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_tmp2_ = command;
#line 36 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_tmp3_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp1_, _tmp2_);
#line 36 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	cmd = (FsoGsmAtCommand*) _tmp3_;
#line 37 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	_vala_assert (cmd != NULL, "cmd != null");
#line 38 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	result = cmd;
#line 38 "/tmp/buildd/fso-gsmd-0.12.0/tests/testatcommand.vala"
	return result;
#line 102 "testatcommand.c"
}
