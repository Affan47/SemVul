initMapVision()
{
	if(!_vision){
		_theight = _map->getHeight();
		int width = _map->getWidth();
		_vision = new int * [ _theight ];
		for( int i = 0; i < _theight; i++ ) {
			_vision[i] = new int [ width ];
			for( int j = 0; j < width; j++ ) {
				_vision[i][j] = 0;
			}
		}
	}
}
