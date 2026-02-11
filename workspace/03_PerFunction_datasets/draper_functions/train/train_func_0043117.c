del(ObjHandle h)
{
	if (!validHandle(h)) return false;
	freeObj(remove(h));
	return true;
}
