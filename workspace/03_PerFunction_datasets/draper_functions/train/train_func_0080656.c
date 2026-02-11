slot_ownResource( int num )
{
	ResourceModel * model = DataTheme.resources.get( num );
	if( model->isPreservable() ){
		return;
	}

	_icoLeft->setResource( num );
	_isLeft = true;
	_resource = num;
	setValue( 0 );
	_icoRight->setValue( QString::number( 0 ) );
	if( _isRight ) {
		 if(_prices->getResourcePrice( _resource ) > _prices->getResourcePrice( _other )){
			_cost = _prices->getResourceInResource(  _resource ,_other);
		 } else {
			_cost = _prices->getResourceInResource( _other,_resource);
		 }
		_scroll->setEnabled( true );
		_butBuy->setEnabled( true );
		_butAll->setEnabled( true );
	}
}
