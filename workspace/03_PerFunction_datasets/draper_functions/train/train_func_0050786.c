getCharacName( LordCharac charac )
{
	QString ret = "";
	switch( charac ) {
	case ATTACK:
		ret = "attack";
		break;
	case DEFENSE:
		ret = "defense";
		break;
	case POWER:
		ret = "power";
		break;
	case KNOWLEDGE:
		ret = "knowledge";
		break;
	case MOVE:
		ret = "move";
		break;
	case MAXMOVE:
		ret = "movemax";
		break;
	case TECHNICPOINT:
		ret = "technicpoint";
		break;
	case MAXTECHNICPOINT:
		ret = "maxtechnicpoint";
		break;
	case MORALE:
		ret = "morale";
		break;
	case LUCK:
		ret = "luck";
		break;
	case VISION:
		ret = "vision";
		break;
	case EXPERIENCE:
		ret = "experience";
		break;
	case CHARISMA:
		ret = "charisma";
		break;
	case LEVEL:
		ret = "level";
		break;
	default:
		break;
	}

	return ret;
}
