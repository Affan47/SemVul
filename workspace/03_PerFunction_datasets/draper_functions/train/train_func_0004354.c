gee_hazard_pointer_acquire (void) {
	GeeHazardPointerNode* result = NULL;
	GeeHazardPointerNode* node = NULL;
	GeeHazardPointerNode* _tmp9_ = NULL;
	GeeHazardPointerNode* old_head = NULL;
	GeeHazardPointerNode* _tmp18_ = NULL;
	{
		GeeHazardPointerNode* curr = NULL;
		GeeHazardPointerNode* _tmp0_ = NULL;
		_tmp0_ = gee_hazard_pointer_get_head ();
		curr = _tmp0_;
		{
			gboolean _tmp1_ = FALSE;
			_tmp1_ = TRUE;
			while (TRUE) {
				gboolean _tmp2_ = FALSE;
				GeeHazardPointerNode* _tmp5_ = NULL;
				GeeHazardPointerNode* _tmp6_ = NULL;
				gboolean _tmp7_ = FALSE;
				_tmp2_ = _tmp1_;
				if (!_tmp2_) {
					GeeHazardPointerNode* _tmp3_ = NULL;
					GeeHazardPointerNode* _tmp4_ = NULL;
					_tmp3_ = curr;
					_tmp4_ = gee_hazard_pointer_node_get_next (_tmp3_);
					curr = _tmp4_;
				}
				_tmp1_ = FALSE;
				_tmp5_ = curr;
				if (!(_tmp5_ != NULL)) {
					break;
				}
				_tmp6_ = curr;
				_tmp7_ = gee_hazard_pointer_node_activate (_tmp6_);
				if (_tmp7_) {
					GeeHazardPointerNode* _tmp8_ = NULL;
					_tmp8_ = curr;
					result = _tmp8_;
					return result;
				}
			}
		}
	}
	_tmp9_ = gee_hazard_pointer_node_new ();
	node = _tmp9_;
	old_head = NULL;
	{
		gboolean _tmp10_ = FALSE;
		_tmp10_ = TRUE;
		while (TRUE) {
			gboolean _tmp11_ = FALSE;
			GeeHazardPointerNode* _tmp15_ = NULL;
			void* _tmp16_ = NULL;
			GeeHazardPointerNode* _tmp17_ = NULL;
			_tmp11_ = _tmp10_;
			if (!_tmp11_) {
				GeeHazardPointerNode* _tmp12_ = NULL;
				GeeHazardPointerNode* _tmp13_ = NULL;
				gboolean _tmp14_ = FALSE;
				_tmp12_ = old_head;
				_tmp13_ = node;
				_tmp14_ = g_atomic_pointer_compare_and_exchange ((volatile gpointer *) (&gee_hazard_pointer__head), _tmp12_, _tmp13_);
				if (!(!_tmp14_)) {
					break;
				}
			}
			_tmp10_ = FALSE;
			_tmp15_ = node;
			_tmp16_ = g_atomic_pointer_get ((volatile gpointer *) (&gee_hazard_pointer__head));
			old_head = (GeeHazardPointerNode*) _tmp16_;
			_tmp17_ = old_head;
			gee_hazard_pointer_node_set_next (_tmp15_, _tmp17_);
		}
	}
	_tmp18_ = node;
	result = _tmp18_;
	return result;
}
