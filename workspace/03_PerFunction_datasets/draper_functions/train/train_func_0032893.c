getOption(const char* name, FindType ft) const {
	return !allowUnreg_ ? *pv_.ctx->find(name, ft) : tryGetOption(name, ft);
}
