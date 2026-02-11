addobj(obj)
{
	if(object1 != 0)
		return;
	if(object != 0) {
		object1 = -1;
		return;
	}
	object = obj;
}
