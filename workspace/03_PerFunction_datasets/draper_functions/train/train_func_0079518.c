welded(obj)
register struct obj *obj;
{
	if (obj && obj == uwep && will_weld(obj)) {
		obj->bknown = TRUE;
		return 1;
	}
	return 0;
}
