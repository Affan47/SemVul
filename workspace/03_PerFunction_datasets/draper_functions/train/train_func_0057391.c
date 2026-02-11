handlePropertiesBase()
{
	PropertiesBase * propBase = new PropertiesBase( & _players );
	propBase->init( _currentCell->getBase() );
	propBase->exec();

	delete propBase;
}
