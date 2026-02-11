findproxy_mode(const char *name, int mode, int cap) {

	struct proxy *curproxy, *target = NULL;

	for (curproxy = proxy; curproxy; curproxy = curproxy->next) {
		if ((curproxy->cap & cap)!=cap || strcmp(curproxy->id, name))
			continue;

		if (curproxy->mode != mode &&
		    !(curproxy->mode == PR_MODE_HTTP && mode == PR_MODE_TCP)) {
			Alert("Unable to use proxy '%s' with wrong mode, required: %s, has: %s.\n",
				name, proxy_mode_str(mode), proxy_mode_str(curproxy->mode));
			Alert("You may want to use 'mode %s'.\n", proxy_mode_str(mode));
			return NULL;
		}

		if (!target) {
			target = curproxy;
			continue;
		}

		Alert("Refusing to use duplicated proxy '%s' with overlapping capabilities: %s/%s!\n",
			name, proxy_type_str(curproxy), proxy_type_str(target));

		return NULL;
	}

	return target;
}
