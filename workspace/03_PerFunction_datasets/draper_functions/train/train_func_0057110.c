convert_sb(obj)
CcWnnObject obj;
{
    if (JCBUF(obj)->nClause == 0) {
	send_back(obj);
	fix(obj);
    } else {
	convert_general(obj, 0);
    }
}
