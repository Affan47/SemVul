merge_helpname(struct valname *src, struct valexpr *dest)
{
	switch  (dest->val_op)  {
	default:
		return;
	case  VAL_NAME:
		merge_helpname_name(src, dest->val_un.val_name);
		return;
	case  VAL_ROUND:
	case  '+':
	case  '-':
	case  '*':
	case  '/':
	case  '%':
		merge_helpname(src, dest->val_left);
		merge_helpname(src, dest->val_un.val_right);
		return;
	}
}
