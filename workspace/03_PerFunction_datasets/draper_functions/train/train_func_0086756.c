ret()
{
#ifdef FRAMEPOINTER
    offset_T newsp;

    if (framep != 0)
    {
	newsp = -(offset_T) func1saveregsize;
	if (switchnow != NULL || newsp - sp >= 0x80)
	    changesp(newsp, TRUE);
	else
	    modstk(newsp);
	popframe();
    }
    outreturn();
#else
# ifdef MC6809
    store_pt reglist;

    switch (sp)
    {
    case -1:
	reglist = JUNK1REGS | PCREG;
	break;
    case -2:
	reglist = JUNK2REGS | PCREG;
	break;
    case -3:
	reglist = JUNK3REGS | PCREG;
	break;
    case -4:
	reglist = JUNK4REGS | PCREG;
	break;
    default:
	modstk(0);
	outreturn();
	return;
    }
    poplist(reglist);
#else
    if (sp != 0)
    {
	modstk(-(offset_T) func1saveregsize);
	poplist(callee1mask);
    }
    outreturn();
# endif
#endif
}
