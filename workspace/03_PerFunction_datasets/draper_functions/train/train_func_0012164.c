staff_member_find(symtab_ty *stp, string_ty *key)
{
    staff_member_ty *mp;

    mp = (staff_member_ty *)stp->query(key);
    if (!mp)
    {
	mp = staff_member_new();
	stp->assign(key, mp);
    }
    return mp;
}
