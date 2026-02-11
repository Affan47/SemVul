make_thread_name(const string &given_name) {
	if (given_name.empty()) {
		if (OXT_LIKELY(global_context != NULL)) {
			stringstream str;
			str << "Thread #";
			{
				boost::lock_guard<boost::mutex> l(global_context->thread_registration_mutex);
				str << global_context->next_thread_number;
			}
			return str.str();
		} else {
			return "(unknown)";
		}
	} else {
		return given_name;
	}
}
