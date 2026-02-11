projects_construct (GType object_type) {
	Projects* self = NULL;
	GeeLinkedList* _tmp0_ = NULL;
	GFile* file = NULL;
	GFile* _tmp1_ = NULL;
	GFile* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	gchar* contents = NULL;
	GFile* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	GError * _inner_error_ = NULL;
	self = (Projects*) g_type_create_instance (object_type);
	_tmp0_ = gee_linked_list_new (TYPE_PROJECT, (GBoxedCopyFunc) project_dup, project_free, NULL);
	_g_object_unref0 (self->priv->projects);
	self->priv->projects = _tmp0_;
	_tmp1_ = projects_get_xml_file (self);
	file = _tmp1_;
	_tmp2_ = file;
	_tmp3_ = g_file_query_exists (_tmp2_, NULL);
	if (!_tmp3_) {
		_g_object_unref0 (file);
		return self;
	}
	_tmp4_ = file;
	_tmp5_ = utils_load_file (_tmp4_);
	contents = _tmp5_;
	_tmp6_ = contents;
	if (_tmp6_ == NULL) {
		_g_free0 (contents);
		_g_object_unref0 (file);
		return self;
	}
	{
		GMarkupParser parser = {0};
		GMarkupParser _tmp7_ = {0};
		GMarkupParseContext* context = NULL;
		GMarkupParser _tmp8_ = {0};
		GMarkupParseContext* _tmp9_ = NULL;
		GMarkupParseContext* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		_tmp7_.start_element = _projects_parser_start_gmarkup_parser_start_element_func;
		_tmp7_.end_element = NULL;
		_tmp7_.text = NULL;
		_tmp7_.passthrough = NULL;
		_tmp7_.error = NULL;
		parser = _tmp7_;
		_tmp8_ = parser;
		_tmp9_ = g_markup_parse_context_new (&_tmp8_, 0, self, NULL);
		context = _tmp9_;
		_tmp10_ = context;
		_tmp11_ = contents;
		g_markup_parse_context_parse (_tmp10_, _tmp11_, (gssize) (-1), &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_markup_parse_context_unref0 (context);
			goto __catch51_g_error;
		}
		projects_update_all_documents (self);
		projects_update_all_menus (self);
		_g_markup_parse_context_unref0 (context);
	}
	goto __finally51;
	__catch51_g_error:
	{
		GError* e = NULL;
		GError* _tmp12_ = NULL;
		const gchar* _tmp13_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp12_ = e;
		_tmp13_ = _tmp12_->message;
		g_warning ("projects.vala:59: Impossible to load the projects: %s", _tmp13_);
		_g_error_free0 (e);
	}
	__finally51:
	if (_inner_error_ != NULL) {
		_g_free0 (contents);
		_g_object_unref0 (file);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_g_free0 (contents);
	_g_object_unref0 (file);
	return self;
}
