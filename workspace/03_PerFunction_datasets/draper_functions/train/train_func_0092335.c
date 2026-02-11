getOption() {
    if (NextOpt != Options.end()) {
	TOptList::iterator it = NextOpt;
	++NextOpt;
	return (*it);
    }
    return 0;
}
