File(int index) {
    if (rep_->dir == nil) {
	return nil;
    }
    const _lib_os(String)* s = rep_->dir->name(index);
    if (s == nil) {
	return nil;
    }
    return s->string();
}
