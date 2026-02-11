linkDestroyed(QObject *qobject)
{
	void *object = _link_map.value(qobject, 0);
	_link_map.remove(qobject);
	if (object)
		GB.Unref(POINTER(&object));
}
