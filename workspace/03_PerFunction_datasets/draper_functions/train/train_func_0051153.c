you_have(int mask)
{
    switch(mask)
    {
    case M3_WANTSAMUL:	return(bool)(u.uhave.amulet);
    case M3_WANTSBELL:	return(bool)(u.uhave.bell);
    case M3_WANTSCAND:	return(bool)(u.uhave.menorah);
    case M3_WANTSBOOK:	return(bool)(u.uhave.book);
    case M3_WANTSARTI:	return(bool)(u.uhave.questart);
    default:		break;
    }
    return(0);
}
