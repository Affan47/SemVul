XpTableLocLen( loc)
    XpTableLoc  loc;
{
    int i = 0;

    for ( i = 0 ;  loc && loc->w_quark != NULLQUARK  ; loc++ )
	i++;
    return i;
}
