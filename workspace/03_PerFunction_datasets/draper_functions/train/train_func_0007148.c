clear()
{
	_name->setValue( "" );
	_category->setCurrentItem( 0 );
	_attack->setValue( 1 );
	_defense->setValue( 1 );
	_power->setValue( 0 );
	_knowledge->setValue( 0 );
	_charisma->setValue( 1 );
	_movemax->setValue( 16 );
	_vision->setValue( 5 );
	_troops->clear();
	_bigPix->setValue( "" );
	_smallPix->setValue( "" );
}
