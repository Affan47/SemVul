db_clear_object_flag(Objid oid, db_object_flag f)
{
    objects[oid]->flags &= ~(1 << f);
    if (f == FLAG_USER) {
	Var v;

	v.type = TYPE_OBJ;
	v.v.obj = oid;
	all_users = setremove(all_users, v);
    }
}
