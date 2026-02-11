__lambda137_ (Latexila* self) {
	MainWindow* _tmp0_ = NULL;
	MainWindow* _tmp1_ = NULL;
	g_application_hold ((GApplication*) self);
	_tmp0_ = latexila_create_window (self);
	_tmp1_ = _tmp0_;
	_g_object_unref0 (_tmp1_);
	g_application_release ((GApplication*) self);
}
