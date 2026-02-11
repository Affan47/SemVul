p11_get_session(hx509_context context,
		struct p11_module *p,
		struct p11_slot *slot,
		hx509_lock lock,
		CK_SESSION_HANDLE *psession)
{
    CK_RV ret;

    if (slot->flags & P11_SESSION_IN_USE)
	_hx509_abort("slot already in session");

    if (slot->flags & P11_SESSION) {
	slot->flags |= P11_SESSION_IN_USE;
	*psession = slot->session;
	return 0;
    }

    ret = P11FUNC(p, OpenSession, (slot->id,
				   CKF_SERIAL_SESSION,
				   NULL,
				   NULL,
				   &slot->session));
    if (ret != CKR_OK) {
	if (context)
	    hx509_set_error_string(context, 0, HX509_PKCS11_OPEN_SESSION,
				   "Failed to OpenSession for slot id %d "
				   "with error: 0x%08x",
				   (int)slot->id, ret);
	return HX509_PKCS11_OPEN_SESSION;
    }

    slot->flags |= P11_SESSION;


    if (   (slot->flags & P11_LOGIN_REQ)
	&& (slot->flags & P11_LOGIN_DONE) == 0
	&& (lock || slot->pin))
    {
	hx509_prompt prompt;
	char pin[20];
	char *str;

	if (slot->pin == NULL) {

	    memset(&prompt, 0, sizeof(prompt));

	    ret = asprintf(&str, "PIN code for %s: ", slot->name);
	    if (ret == -1 || str == NULL) {
		if (context)
		    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
		return ENOMEM;
	    }
	    prompt.prompt = str;
	    prompt.type = HX509_PROMPT_TYPE_PASSWORD;
	    prompt.reply.data = pin;
	    prompt.reply.length = sizeof(pin);

	    ret = hx509_lock_prompt(lock, &prompt);
	    if (ret) {
		free(str);
		if (context)
		    hx509_set_error_string(context, 0, ret,
					   "Failed to get pin code for slot "
					   "id %d with error: %d",
					   (int)slot->id, ret);
		return ret;
	    }
	    free(str);
	} else {
	    strlcpy(pin, slot->pin, sizeof(pin));
	}

	ret = P11FUNC(p, Login, (slot->session, CKU_USER,
				 (unsigned char*)pin, strlen(pin)));
	if (ret != CKR_OK) {
	    if (context)
		hx509_set_error_string(context, 0, HX509_PKCS11_LOGIN,
				       "Failed to login on slot id %d "
				       "with error: 0x%08x",
				       (int)slot->id, ret);
	    return HX509_PKCS11_LOGIN;
	} else
	    slot->flags |= P11_LOGIN_DONE;

	if (slot->pin == NULL) {
	    slot->pin = strdup(pin);
	    if (slot->pin == NULL) {
		if (context)
		    hx509_set_error_string(context, 0, ENOMEM,
					   "out of memory");
		return ENOMEM;
	    }
	}
    } else
	slot->flags |= P11_LOGIN_DONE;

    slot->flags |= P11_SESSION_IN_USE;

    *psession = slot->session;

    return 0;
}
