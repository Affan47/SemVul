add(const std::string& name, const std::string& value) {
	OptionContext::option_iterator it = ctx->tryFind(name.c_str());
	if (it != ctx->end()) {
		add(*it, value);
	}
}
