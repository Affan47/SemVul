unlinknp(void) {

	if(haskey(& rc, "np-file")) {
		const char * np = value(& rc, "np-file");
		if(np != NULL)
			unlink(np);
	}
}
