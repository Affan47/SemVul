reorientation_con(orientation, rotation)
char	orientation;
char	rotation;
{
	int	face = 0;

	switch (rotation) {
	case NOSYM :
		switch (orientation) {
		case 'N' :
			face = NORD;
			break;
		case 'E' :
			face = EST;
			break;
		case 'S' :
			face = SUD;
			break;
		case 'W' :
			face = OUEST;
			break;
		}
		break;

	case ROT_P :
		switch (orientation) {
		case 'N' :
			face = OUEST;
			break;
		case 'E' :
			face = NORD;
			break;
		case 'S' :
			face = EST;
			break;
		case 'W' :
			face = SUD;
			break;
		}
		break;
	case SYMXY :
		switch (orientation) {
		case 'N' :
			face = SUD;
			break;
		case 'E' :
			face = OUEST;
			break;
		case 'S' :
			face = NORD;
			break;
		case 'W' :
			face = EST;
			break;
		}
		break;
	case ROT_M :
		switch (orientation) {
		case 'N' :
			face = EST;
			break;
		case 'E' :
			face = SUD;
			break;
		case 'S' :
			face = OUEST;
			break;
		case 'W' :
			face = NORD;
			break;
		}
		break;
	case SYM_X :
		switch (orientation) {
		case 'N' :
			face = NORD;
			break;
		case 'E' :
			face = OUEST;
			break;
		case 'S' :
			face = SUD;
			break;
		case 'W' :
			face = EST;
			break;
		}
		break;
	case SY_RM :
		switch (orientation) {
		case 'N' :
			face = OUEST;
			break;
		case 'E' :
			face = SUD;
			break;
		case 'S' :
			face = EST;
			break;
		case 'W' :
			face = NORD;
			break;
		}
		break;
	case SYM_Y :
		switch (orientation) {
		case 'N' :
			face = SUD;
			break;
		case 'E' :
			face = EST;
			break;
		case 'S' :
			face = NORD;
			break;
		case 'W' :
			face = OUEST;
			break;
		}
		break;
	case SY_RP :
		switch (orientation) {
		case 'N' :
			face = EST;
			break;
		case 'E' :
			face = NORD;
			break;
		case 'S' :
			face = OUEST;
			break;
		case 'W' :
			face = SUD;
			break;
		}
		break;
	}

	return(face);
}
