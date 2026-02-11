db_count_verbs(Objid oid)
{
    int count = 0;
    Object *o = dbpriv_find_object(oid);
    Verbdef *v;

    for (v = o->verbdefs; v; v = v->next)
	count++;

    return count;
}
