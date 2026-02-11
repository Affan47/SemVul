slot_otherResource( int num )
{
	ResourceModel * model = DataTheme.resources.get( num );
	if( model->isPreservable() ){
		return;
	}

	_other= num;
	_icoRight->setResource( num );
	_isRight = true;
	_icoRight->setValue( QString::number( 0 ) );
	_icoLeft->setValue( QString::number( 0 ) );
	if( _isLeft ) {
		if(_prices->getResourcePrice( _other ) > _prices->getResourcePrice( _resource )){
			_cost = _prices->getResourceInResource(  _other , _resource);
			_first=false;
		 } else {
			_cost = _prices->getResourceInResource(  _resource ,_other);
			_first=true;
		 }
		_scroll->setEnabled( true );
		_butBuy->setEnabled( true );
		_butAll->setEnabled( true );
	}
}
