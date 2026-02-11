rest(const char * method, struct hash * p) {
	char ** response, * json;

	if(haskey(& rc, "session")) {
		set(p, "sk", value(& rc, "session"));
	}

	set(p, "format", "json");
	set(p, "method", method);
	set(p, "api_key", API_KEY);
	set(p, "api_sig", build_signature(p));

	debug("rest call signuture: <%s>\n", value(p, "api_sig"));

	response = fetch(REST_API_BASE, NULL, hash_query(p), NULL);
	json = join(response, 0);

	debug("response:\n%s\n", json);

	return json;
}
