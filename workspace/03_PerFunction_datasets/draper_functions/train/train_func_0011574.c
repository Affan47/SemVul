clear()
{
	_default = "";
	while( ! _list.isEmpty() ) {
		delete _list.takeFirst();
	}
}
