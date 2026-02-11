trverb()
{
	switch(verb){
	case CALM:
	case WALK:
	case QUIT:
	case SCORE:
	case FOO:
	case BRIEF:
	case SUSPEND:
	case HOURS:
	case LOG:
		actspk(verb);
		break;
	case TAKE:
		vtake();
		break;
	case DROP:
		vdrop();
		break;
	case OPEN:
	case LOCK:
		vopen();
		break;
	case SAY:
		vsay();
		break;
	case NOTHING:
		rspeak(54);
		break;
	case ON:
		von();
		break;
	case OFF:
		voff();
		break;
	case WAVE:
		vwave();
		break;
	case KILL:
		vkill();
		break;
	case POUR:
		vpour();
		break;
	case EAT:
		veat();
		break;
	case DRINK:
		vdrink();
		break;
	case RUB:
		if (object != LAMP)
			rspeak(76);
		else
			actspk(RUB);
		break;
	case THROW:
		vthrow();
		break;
	case FEED:
		vfeed();
		break;
	case FIND:
	case INVENTORY:
		vfind();
		break;
	case FILL:
		vfill();
		break;
	case READ:
		vread();
		break;
	case BLAST:
		vblast();
		break;
	case BREAK:
		vbreak();
		break;
	case WAKE:
		vwake();
		break;
	default:
		printf("This verb is not implemented yet.\n");
	}
}
