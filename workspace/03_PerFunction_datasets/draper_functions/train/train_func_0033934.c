backtrace() const throw() {
	#ifdef OXT_BACKTRACE_IS_ENABLED
		spin_lock::scoped_lock l(context->backtrace_lock);
		return format_backtrace(context->backtrace_list);
	#else
		return "    (backtrace support disabled during compile time)";
	#endif
}
