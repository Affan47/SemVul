_delete(Request& r, MethodParams& params) {
	VHashfile& self=GET_SELF(r, VHashfile);

	if(!params.count()) {

		self.delete_files();
		return;
	}

	const String &key=params.as_string(0, "key must be string");

	self.remove(key);
}
