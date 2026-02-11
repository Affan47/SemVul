aa_alloc_profile(const char *hname, struct aa_proxy *proxy,
				    gfp_t gfp)
{
	struct aa_profile *profile;


	profile = kzalloc(sizeof(*profile) + sizeof (struct aa_profile *) * 2,
			  gfp);
	if (!profile)
		return NULL;

	if (!aa_policy_init(&profile->base, NULL, hname, gfp))
		goto fail;
	if (!aa_label_init(&profile->label, 1))
		goto fail;


	if (!proxy) {
		proxy = aa_alloc_proxy(&profile->label, gfp);
		if (!proxy)
			goto fail;
	} else
		aa_get_proxy(proxy);
	profile->label.proxy = proxy;

	profile->label.hname = profile->base.hname;
	profile->label.flags |= FLAG_PROFILE;
	profile->label.vec[0] = profile;


	return profile;

fail:
	aa_free_profile(profile);

	return NULL;
}
