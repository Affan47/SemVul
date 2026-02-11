tracker_store_commit_type (TrackerStoreTask* task) {
	TrackerDataCommitType result = 0;
	TrackerStoreTask* _tmp0_;
	TrackerStoreTaskType _tmp1_;
#line 139 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	g_return_val_if_fail (task != NULL, 0);
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	_tmp0_ = task;
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	_tmp1_ = _tmp0_->type;
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
	switch (_tmp1_) {
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
		case TRACKER_STORE_TASK_TYPE_UPDATE:
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
		case TRACKER_STORE_TASK_TYPE_UPDATE_BLANK:
#line 915 "tracker-store.c"
		{
			TrackerStoreTask* _tmp2_;
			TrackerStorePriority _tmp3_;
#line 143 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			_tmp2_ = task;
#line 143 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			_tmp3_ = G_TYPE_CHECK_INSTANCE_CAST (_tmp2_, TRACKER_STORE_TYPE_UPDATE_TASK, TrackerStoreUpdateTask)->priority;
#line 143 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			if (_tmp3_ == TRACKER_STORE_PRIORITY_HIGH) {
#line 144 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				result = TRACKER_DATA_COMMIT_REGULAR;
#line 144 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				return result;
#line 929 "tracker-store.c"
			} else {
				GQueue* _tmp4_;
				guint _tmp5_ = 0U;
#line 145 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				_tmp4_ = tracker_store_update_queues[TRACKER_STORE_PRIORITY_LOW];
#line 145 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				_tmp5_ = g_queue_get_length (_tmp4_);
#line 145 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				if (_tmp5_ > ((guint) 0)) {
#line 146 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
					result = TRACKER_DATA_COMMIT_BATCH;
#line 146 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
					return result;
#line 943 "tracker-store.c"
				} else {
#line 148 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
					result = TRACKER_DATA_COMMIT_BATCH_LAST;
#line 148 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
					return result;
#line 949 "tracker-store.c"
				}
			}
		}
#line 140 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
		case TRACKER_STORE_TASK_TYPE_TURTLE:
#line 955 "tracker-store.c"
		{
			GQueue* _tmp6_;
			guint _tmp7_ = 0U;
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			_tmp6_ = tracker_store_update_queues[TRACKER_STORE_PRIORITY_TURTLE];
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			_tmp7_ = g_queue_get_length (_tmp6_);
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			if (_tmp7_ > ((guint) 0)) {
#line 152 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				result = TRACKER_DATA_COMMIT_BATCH;
#line 152 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				return result;
#line 969 "tracker-store.c"
			} else {
#line 154 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				result = TRACKER_DATA_COMMIT_BATCH_LAST;
#line 154 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
				return result;
#line 975 "tracker-store.c"
			}
		}
		default:
		{
#line 157 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			g_warn_if_reached ();
#line 158 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			result = TRACKER_DATA_COMMIT_REGULAR;
#line 158 "/home/martyn/Source/tracker/src/tracker-store/tracker-store.vala"
			return result;
#line 986 "tracker-store.c"
		}
	}
}
