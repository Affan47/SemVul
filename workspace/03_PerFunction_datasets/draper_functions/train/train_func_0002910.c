ccpu_info(void *context, int regnum)
{
	static char buffer[16][47+1];
	static int which = 0;
	CONTEXTCCPU *r = context;

	which = (which+1) % 16;
    buffer[which][0] = '\0';
	if( !context )
	{
        static CONTEXTCCPU tmp;
		cGetContext(&tmp);
		r = &tmp;
	}

    switch( regnum )
	{
        case CPU_INFO_REG+CCPU_PC: sprintf(buffer[which], "PC:%04X", r->eRegPC); break;
		case CPU_INFO_REG+CCPU_CFLAG: sprintf(buffer[which], "C:%02X", r->cFlag); break;
        case CPU_INFO_REG+CCPU_CSTATE: sprintf(buffer[which], "S:%X", r->eCState); break;
		case CPU_INFO_REG+CCPU_A: sprintf(buffer[which], "A:%03X", r->eRegA); break;
		case CPU_INFO_REG+CCPU_B: sprintf(buffer[which], "B:%03X", r->eRegB); break;
		case CPU_INFO_REG+CCPU_I: sprintf(buffer[which], "I:%03X", r->eRegI); break;
        case CPU_INFO_REG+CCPU_P: sprintf(buffer[which], "P:%X", r->eRegP); break;
		case CPU_INFO_REG+CCPU_J: sprintf(buffer[which], "J:%03X", r->eRegJ); break;
		case CPU_INFO_REG+CCPU_ACC: sprintf(buffer[which], "ACC:%03X", r->accVal); break;
        case CPU_INFO_REG+CCPU_CMP: sprintf(buffer[which], "CMP:%03X", r->cmpVal); break;
        case CPU_INFO_REG+CCPU_PA0: sprintf(buffer[which], "PA0:%02X", r->pa0); break;
			break;
		case CPU_INFO_FLAGS:

			sprintf(buffer[which], "%c-%c%c%c%c",
				(r->cFlag) ? 'C' : 'c',
                (r->eCState == state_A || r->eCState == state_AA) ? 'A':' ',
                (r->eCState == state_A) ? 'A':' ',
                (r->eCState == state_B || r->eCState == state_BB) ? 'B':' ',
                (r->eCState == state_B) ? 'B':' ');
            break;
		case CPU_INFO_NAME: return "CCPU";
		case CPU_INFO_FAMILY: return "Cinematronics CPU";
		case CPU_INFO_VERSION: return "1.0";
		case CPU_INFO_FILE: return __FILE__;
		case CPU_INFO_CREDITS: return "Copyright 1997/1998 Jeff Mitchell and the Retrocade Alliance\nCopyright 1997 Zonn Moore";
		case CPU_INFO_REG_LAYOUT: return (const char *)ccpu_reg_layout;
		case CPU_INFO_WIN_LAYOUT: return (const char *)ccpu_win_layout;
    }
	return buffer[which];

}
