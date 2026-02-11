C_GetFunctionList (CK_FUNCTION_LIST_PTR_PTR list)
{
	return_val_if_fail (list, CKR_ARGUMENTS_BAD);

	*list = &functionList;
	return CKR_OK;
}
