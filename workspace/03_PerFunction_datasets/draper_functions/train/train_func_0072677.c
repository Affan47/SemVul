presufcmp(UNUSED void *instance,
		     REQUEST *req,
		     VALUE_PAIR *request, VALUE_PAIR *check,
		     VALUE_PAIR *check_pairs, UNUSED VALUE_PAIR **reply_pairs)
{
	VALUE_PAIR *vp;
	char *name;
	char rest[MAX_STRING_LEN];
	int len, namelen;
	int ret = -1;

	if (!request) return -1;

	name = request->vp_strvalue;

#if 0
	printf("Comparing %s and %s, check->attr is %d\n",
		name, check->vp_strvalue, check->attribute);
#endif

	len = strlen((char *)check->vp_strvalue);
	switch (check->attribute) {
		case PW_PREFIX:
			ret = strncmp(name, check->vp_strvalue, len);
			if (ret == 0)
				strlcpy(rest, name + len, sizeof(rest));
			break;
		case PW_SUFFIX:
			namelen = strlen(name);
			if (namelen < len)
				break;
			ret = strcmp(name + namelen - len,
					(char *)check->vp_strvalue);
			if (ret == 0) {
				strlcpy(rest, name, namelen - len + 1);
			}
			break;
	}
	if (ret != 0)
		return ret;


	vp = pairfind(check_pairs, PW_STRIP_USER_NAME);
	if (vp && !vp->vp_integer) return ret;


	vp = pairfind(check_pairs, PW_STRIPPED_USER_NAME);
	if (!vp) {


		vp = radius_paircreate(req, &request,
				       PW_STRIPPED_USER_NAME, PW_TYPE_STRING);
		if (!vp) return ret;
		req->username = vp;
	}

	strlcpy((char *)vp->vp_strvalue, rest, sizeof(vp->vp_strvalue));
	vp->length = strlen(vp->vp_strvalue);

	return ret;
}
