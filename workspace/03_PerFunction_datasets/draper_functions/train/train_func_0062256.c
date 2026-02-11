fso_data_mbpi_database_handleChildren (FsoDataMBPIDatabase* self, xmlNode* node) {
	g_return_if_fail (self != NULL);
	{
		xmlNode* iter = NULL;
		xmlNode* _tmp0_ = NULL;
		xmlNode* _tmp1_ = NULL;
		_tmp0_ = node;
		_tmp1_ = _tmp0_->children;
		iter = _tmp1_;
		{
			gboolean _tmp2_ = FALSE;
			_tmp2_ = TRUE;
			while (TRUE) {
				gboolean _tmp3_ = FALSE;
				xmlNode* _tmp6_ = NULL;
				xmlNode* _tmp7_ = NULL;
				xmlElementType _tmp8_ = 0;
				gchar* node_name = NULL;
				xmlNode* _tmp9_ = NULL;
				const gchar* _tmp10_ = NULL;
				gchar* _tmp11_ = NULL;
				gchar* node_content = NULL;
				xmlNode* _tmp12_ = NULL;
				gchar* _tmp13_ = NULL;
				xmlNode* _tmp14_ = NULL;
				_tmp3_ = _tmp2_;
				if (!_tmp3_) {
					xmlNode* _tmp4_ = NULL;
					xmlNode* _tmp5_ = NULL;
					_tmp4_ = iter;
					_tmp5_ = _tmp4_->next;
					iter = _tmp5_;
				}
				_tmp2_ = FALSE;
				_tmp6_ = iter;
				if (!(_tmp6_ != NULL)) {
					break;
				}
				_tmp7_ = iter;
				_tmp8_ = _tmp7_->type;
				if (_tmp8_ != XML_ELEMENT_NODE) {
					continue;
				}
				_tmp9_ = iter;
				_tmp10_ = _tmp9_->name;
				_tmp11_ = g_strdup (_tmp10_);
				node_name = _tmp11_;
				_tmp12_ = iter;
				_tmp13_ = (gchar*) xmlNodeGetContent (_tmp12_);
				node_content = _tmp13_;
				_tmp14_ = iter;
				fso_data_mbpi_database_parseNode (self, _tmp14_);
				_g_free0 (node_content);
				_g_free0 (node_name);
			}
		}
	}
}
