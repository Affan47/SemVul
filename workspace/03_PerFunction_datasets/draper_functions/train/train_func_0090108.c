profile_free(Profile *profile)
{
	if (profile == NULL)
		return;

	Section *sp = profile->sections;
	while (sp != NULL) {
		Section *st = sp;
		KeyValue *kvp = sp->pairs;

		while (kvp != NULL) {
			KeyValue *kvt = kvp;

			vm_free(kvp->key);
			vm_free(kvp->value);

			kvp = kvp->next;
			vm_free(kvt);
		}

		vm_free(sp->name);

		sp = sp->next;
		vm_free(st);
	}

	vm_free(profile);
}
