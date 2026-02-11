endFill()
{

	if ( _currpath && _currfill )
	{


		_currpath->close();


		_x = _currpath->ap.x;
		_y = _currpath->ap.y;
	}

	if (_currline) {
		_shape.addSubshape(_currsubshape);
		_currsubshape.paths().clear();
	}


	_currpath = 0;

	_currfill = 0;
}
