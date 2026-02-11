f_blkfree(VALUE *vp)
{
	int id;
	VALUE result;


	result.v_type = V_NULL;
	result.v_subtype = V_NOSUBTYPE;

	id = 0;
	switch (vp->v_type) {
		case V_NBLOCK:
			id = vp->v_nblock->id;
			break;
		case V_STR:
			id = findnblockid(vp->v_str->s_str);
			if (id < 0)
				return error_value(E_BLKFREE1);
			break;
		case V_NUM:
			if (qisfrac(vp->v_num) || qisneg(vp->v_num))
				return error_value(E_BLKFREE2);
			if (zge31b(vp->v_num->num))
				return error_value(E_BLKFREE3);
			id = qtoi(vp->v_num);
			break;
		default:
			return error_value(E_BLKFREE4);
	}
	id = removenblock(id);
	if (id)
		return error_value(id);
	return result;
}
