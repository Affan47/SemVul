dvb_timer_get_overlap (time_t this_start, time_t this_end, time_t other_start, time_t other_end) {
	DVBOverlapType result = 0;
	time_t _tmp0_ = 0;
	time_t _tmp1_ = 0;
	_tmp0_ = this_start;
	_tmp1_ = other_start;
	if (_tmp0_ <= _tmp1_) {
		time_t _tmp2_ = 0;
		time_t _tmp3_ = 0;
		_tmp2_ = this_end;
		_tmp3_ = other_start;
		if (_tmp2_ <= _tmp3_) {
			result = DVB_OVERLAP_TYPE_NONE;
			return result;
		} else {
			time_t _tmp4_ = 0;
			time_t _tmp5_ = 0;
			_tmp4_ = this_end;
			_tmp5_ = other_end;
			if (_tmp4_ >= _tmp5_) {
				result = DVB_OVERLAP_TYPE_COMPLETE;
				return result;
			} else {
				result = DVB_OVERLAP_TYPE_PARTIAL;
				return result;
			}
		}
	} else {
		time_t _tmp6_ = 0;
		time_t _tmp7_ = 0;
		_tmp6_ = this_end;
		_tmp7_ = other_end;
		if (_tmp6_ <= _tmp7_) {
			result = DVB_OVERLAP_TYPE_PARTIAL;
			return result;
		} else {
			time_t _tmp8_ = 0;
			time_t _tmp9_ = 0;
			_tmp8_ = this_start;
			_tmp9_ = other_end;
			if (_tmp8_ < _tmp9_) {
				result = DVB_OVERLAP_TYPE_PARTIAL;
				return result;
			} else {
				result = DVB_OVERLAP_TYPE_NONE;
				return result;
			}
		}
	}
}
