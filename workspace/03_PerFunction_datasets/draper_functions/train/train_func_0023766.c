removeResources( GenericResourceList * list )
{
	for( int i = 0; i < count(); i++ ) {
		decreaseValue( i , list->getValue( i ) );
	}

}
