__lambda26_ (Block23Data* _data23_, GSettings* setting, const gchar* key) {
	PreferencesDialog* self;
	gchar* val = NULL;
	GSettings* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	GtkTreeModel* model = NULL;
	GtkTreeModel* _tmp3_ = NULL;
	GtkTreeModel* _tmp4_ = NULL;
	GtkTreeModel* _tmp5_ = NULL;
	GtkTreeIter iter = {0};
	gboolean valid = FALSE;
	GtkTreeModel* _tmp6_ = NULL;
	GtkTreeIter _tmp7_ = {0};
	gboolean _tmp8_ = FALSE;
	self = _data23_->self;
	g_return_if_fail (setting != NULL);
	g_return_if_fail (key != NULL);
	_tmp0_ = setting;
	_tmp1_ = key;
	_tmp2_ = g_settings_get_string (_tmp0_, _tmp1_);
	val = _tmp2_;
	_tmp3_ = gtk_tree_view_get_model (_data23_->schemes_treeview);
	_tmp4_ = _tmp3_;
	_tmp5_ = _g_object_ref0 (_tmp4_);
	model = _tmp5_;
	_tmp6_ = model;
	_tmp8_ = gtk_tree_model_get_iter_first (_tmp6_, &_tmp7_);
	iter = _tmp7_;
	valid = _tmp8_;
	while (TRUE) {
		gboolean _tmp9_ = FALSE;
		gchar* scheme = NULL;
		GtkTreeModel* _tmp10_ = NULL;
		GtkTreeIter _tmp11_ = {0};
		const gchar* _tmp12_ = NULL;
		const gchar* _tmp13_ = NULL;
		GtkTreeModel* _tmp18_ = NULL;
		gboolean _tmp19_ = FALSE;
		_tmp9_ = valid;
		if (!_tmp9_) {
			break;
		}
		_tmp10_ = model;
		_tmp11_ = iter;
		gtk_tree_model_get (_tmp10_, &_tmp11_, PREFERENCES_DIALOG_STYLE_SCHEMES_ID, &scheme, -1, -1);
		_tmp12_ = scheme;
		_tmp13_ = val;
		if (g_strcmp0 (_tmp12_, _tmp13_) == 0) {
			GtkTreeSelection* select = NULL;
			GtkTreeSelection* _tmp14_ = NULL;
			GtkTreeSelection* _tmp15_ = NULL;
			GtkTreeSelection* _tmp16_ = NULL;
			GtkTreeIter _tmp17_ = {0};
			_tmp14_ = gtk_tree_view_get_selection (_data23_->schemes_treeview);
			_tmp15_ = _g_object_ref0 (_tmp14_);
			select = _tmp15_;
			_tmp16_ = select;
			_tmp17_ = iter;
			gtk_tree_selection_select_iter (_tmp16_, &_tmp17_);
			_g_object_unref0 (select);
			_g_free0 (scheme);
			_g_object_unref0 (model);
			_g_free0 (val);
			return;
		}
		_tmp18_ = model;
		_tmp19_ = gtk_tree_model_iter_next (_tmp18_, &iter);
		valid = _tmp19_;
		_g_free0 (scheme);
	}
	_g_object_unref0 (model);
	_g_free0 (val);
}
