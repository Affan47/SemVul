socketModifCreature()
{
	switch( _socket->getCla3() ) {
		case C_CRE_NEW:
		socketModifCreatureNew();
		break;
	case C_CRE_UPDATE:
		socketModifCreatureUpdate();
		break;
	case C_CRE_RESS:
		socketModifCreatureRess();
		break;
	case C_CRE_DEL:
		socketModifCreatureDel();
		break;
	}
}
