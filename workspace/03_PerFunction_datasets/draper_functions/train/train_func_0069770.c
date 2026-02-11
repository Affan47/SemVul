gee_hazard_pointer_get_pointer (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, gconstpointer** aptr, gsize mask, gsize* mask_out) {
	gsize _vala_mask_out = 0UL;
	gpointer result = NULL;
	GeeHazardPointerNode* node = NULL;
	GeeHazardPointerNode* _tmp0_ = NULL;
	void* rptr = NULL;
	void* ptr = NULL;
	gpointer res = NULL;
	void* _tmp14_ = NULL;
	gpointer _tmp15_ = NULL;
	GeeHazardPointerNode* _tmp16_ = NULL;
	_tmp0_ = gee_hazard_pointer_acquire ();
	node = _tmp0_;
	rptr = NULL;
	ptr = NULL;
	_vala_mask_out = (gsize) 0;
	{
		gboolean _tmp1_ = FALSE;
		_tmp1_ = TRUE;
		while (TRUE) {
			gboolean _tmp2_ = FALSE;
			gconstpointer** _tmp6_ = NULL;
			void* _tmp7_ = NULL;
			void* _tmp8_ = NULL;
			gsize _tmp9_ = 0UL;
			void* _tmp10_ = NULL;
			gsize _tmp11_ = 0UL;
			GeeHazardPointerNode* _tmp12_ = NULL;
			void* _tmp13_ = NULL;
			_tmp2_ = _tmp1_;
			if (!_tmp2_) {
				void* _tmp3_ = NULL;
				gconstpointer** _tmp4_ = NULL;
				void* _tmp5_ = NULL;
				_tmp3_ = rptr;
				_tmp4_ = aptr;
				_tmp5_ = g_atomic_pointer_get ((volatile gpointer *) ((void**) _tmp4_));
				if (!(_tmp3_ != _tmp5_)) {
					break;
				}
			}
			_tmp1_ = FALSE;
			_tmp6_ = aptr;
			_tmp7_ = g_atomic_pointer_get ((volatile gpointer *) ((void**) _tmp6_));
			rptr = _tmp7_;
			_tmp8_ = rptr;
			_tmp9_ = mask;
			ptr = (void*) (((gsize) _tmp8_) & (~_tmp9_));
			_tmp10_ = rptr;
			_tmp11_ = mask;
			_vala_mask_out = ((gsize) _tmp10_) & _tmp11_;
			_tmp12_ = node;
			_tmp13_ = ptr;
			gee_hazard_pointer_node_set (_tmp12_, _tmp13_);
		}
	}
	_tmp14_ = ptr;
	_tmp15_ = ((((gconstpointer*) _tmp14_) != NULL) && (g_dup_func != NULL)) ? g_dup_func ((gpointer) ((gconstpointer*) _tmp14_)) : ((gpointer) ((gconstpointer*) _tmp14_));
	res = _tmp15_;
	_tmp16_ = node;
	gee_hazard_pointer_node_release (_tmp16_);
	result = res;
	if (mask_out) {
		*mask_out = _vala_mask_out;
	}
	return result;
}
