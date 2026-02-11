removeTagLiteral() {
	assert(master());
	if (!isSentinel(tag_)) {
		master()->force(tag_, 0);
	}
	tag_ = posLit(0);
}
