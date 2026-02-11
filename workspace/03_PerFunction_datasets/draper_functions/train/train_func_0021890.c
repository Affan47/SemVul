alignWriteMarkX0(AjPAlign thys)
{
    ajint iali;
    ajint nali;

    nali = (ajuint) ajListGetLength(thys->Data);

    for(iali=0; iali < nali; iali++)
	alignWriteMark(thys, iali, 0);

    return;
}
