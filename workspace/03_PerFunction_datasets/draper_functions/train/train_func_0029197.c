displayResource()
{
	QLabel * labResource = new QLabel( this );
	labResource->setText( tr( "Resource: " ) + DataTheme.resources.getRessource( _bonus->getParam( 0 ) ) );
	FIXEDSIZE( labResource );

	_fixed = new AskInt( tr( "Fixed value: " ), this );
	_fixed->setMinValue( 0 );
	_fixed->setMaxValue( 10000 );
	_fixed->setValue( _bonus->getParam( 2 ) );
	FIXEDSIZE( _fixed );

	QVBoxLayout * layout = new QVBoxLayout( this );
	layout->setMargin( 5 );
	layout->setSpacing( 5 );
	layout->addWidget( labResource );
	layout->addWidget( _fixed );
	layout->addStretch( 1 );
	layout->activate();
}
