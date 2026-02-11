socketExch()
{
	ialogV( "SO_EXCH" );

	switch( _socket->getCla2() ) {
	case C_EXCH_START:
		exchangeStart();
		break;
	case C_EXCH_UNIT:
		exchangeUnits();
		break;
	case C_EXCH_ARTEFACT:
		exchangeArtefact();
		break;
	case C_EXCH_BASEUNITCL:
	  	exchangeBaseUnits();
		break;
	default:
		break;
	}
}
