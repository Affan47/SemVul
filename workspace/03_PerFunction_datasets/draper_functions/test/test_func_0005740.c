findGroup(const std::string& name) const {
	std::size_t x = findGroupKey(name);
	if (x < groups_.size()) { return groups_[x]; }
	throw ContextError(caption(), ContextError::unknown_group, name);
}
