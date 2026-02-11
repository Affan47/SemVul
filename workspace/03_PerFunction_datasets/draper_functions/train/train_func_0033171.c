login_prompt_for_specific (CK_FUNCTION_LIST_PTR module, CK_SESSION_HANDLE session,
                           CK_OBJECT_HANDLE object)
{
	GkmWrapPrompt *self;
	CK_ATTRIBUTE attr;
	CK_BBOOL always;
	CK_RV rv;

	g_assert (module);


	g_return_val_if_fail (object != 0, NULL);


	always = CK_FALSE;
	attr.type = CKA_ALWAYS_AUTHENTICATE;
	attr.pValue = &always;
	attr.ulValueLen = sizeof (always);

	rv = (module->C_GetAttributeValue) (session, object, &attr, 1);
	if (rv != CKR_OK || always != CK_TRUE)
		return NULL;

	self = g_object_new (GKM_TYPE_WRAP_PROMPT,
	                     "timeout-seconds", -1,
	                     "bus-name", gkm_wrap_prompt_get_prompter_name (),
	                     NULL);


	self->module = module;
	self->session = session;
	self->object = object;

	return self;
}
