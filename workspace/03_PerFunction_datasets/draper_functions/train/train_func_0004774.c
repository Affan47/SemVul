setPrices( PriceMarket * prices, uchar resource )
{
	QString text;
	ResourceModel * model = DataTheme.resources.get( resource );
	uint nbResources = DataTheme.resources.count();
	for( uint i = 0; i < nbResources; i++ ) {
		ResourceModel * model2 = DataTheme.resources.get( i );
		if( resource == i || model->isPreservable() || model2->isPreservable() ) {

			text = QString("n/a");
		} else if ( prices->getResourcePrice( i ) >= prices->getResourcePrice( resource ) ){

			text = QString::number( prices->getResourceInResource(  i, resource ) );
		} else {

			text = QString("1/%1").arg(  prices->getResourceInResource( resource, i ) );
		}
		_resources[i]->setValue( text );
	}
}
