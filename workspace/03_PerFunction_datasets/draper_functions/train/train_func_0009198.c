emimsg_create_op(int ot, int trn, Octstr *whoami)
{
    int len;
    struct emimsg *ret;

    len = field_count_op(ot, whoami);
    if (len < 0)
	return NULL;
    ret = emimsg_create_withlen(len);
    ret->ot = ot;
    ret->or = 'O';
    ret->trn = trn;
    return ret;
}
