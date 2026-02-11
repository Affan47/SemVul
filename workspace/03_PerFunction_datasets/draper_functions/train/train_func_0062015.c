obj_val() {
	return is_object()||is_command() ? obj_ref() : nil;
}
