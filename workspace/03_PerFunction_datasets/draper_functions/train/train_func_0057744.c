no_match_warning(const char *context) const
{


    PermString keyword = _l.keyword();
    if (!keyword) return;
    if (_l.key_matched()) {
	lwarning(context ? "bad `%s' command in %s:"
		 : "bad `%s' command:", keyword.c_str(), context);
	lwarning("field %d %s", _l.fail_field(), _l.message().c_str());
    } else
	lwarning(context ? "unknown command `%s' in %s"
		 : "unknown command `%s'", keyword.c_str(), context);
    _l.clear_message();
}
