phonesim_remote_phone_control_construct (GType object_type) {
	PhonesimRemotePhoneControl * self = NULL;
	gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	GError * _inner_error_ = NULL;
#line 89 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	self = (PhonesimRemotePhoneControl*) fso_framework_abstract_object_construct (object_type);
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	_tmp1_ = g_dir_make_tmp ("fsogsmd-integration-tests-XXXXXX", &_inner_error_);
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	_tmp0_ = _tmp1_;
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	if (_inner_error_ != NULL) {
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
		g_clear_error (&_inner_error_);
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
		return NULL;
#line 1296 "phonesim_remotecontrol.c"
	}
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	_g_free0 (self->priv->_script_path);
#line 91 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	self->priv->_script_path = _tmp0_;
#line 89 "/tmp/buildd/fso-gsmd-0.12.0/tests/integration/phonesim_remotecontrol.vala"
	return self;
#line 1304 "phonesim_remotecontrol.c"
}
