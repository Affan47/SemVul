test_end(const string&, bool ok, const Time& time)
	{
		if (!(_cur_test->_success = ok))
			++_cur_suite->_errors;
		_cur_test->_time    = time;
	}
