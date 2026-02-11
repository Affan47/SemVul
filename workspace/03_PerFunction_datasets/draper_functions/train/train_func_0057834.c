vxml_parser_notify_text(const vxml_parser_t *vp, const struct vxml_ops *ops)
{
	if (NULL == ops)
		return FALSE;

	if (0 == vxml_output_size(&vp->out))
		return FALSE;


	if (vp->elem_token_valid && ops->tokenized_text != NULL)
		return TRUE;

	return ops->plain_text != NULL;
}
