ensMarkermaplocationTrace(const EnsPMarkermaplocation mml,
                                 ajuint level)
{
    AjPStr indent = NULL;

    if (!mml)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    ajDebug("%SensMarkermaplocationTrace %p\n"
            "%S  Markersynonym %p\n"
            "%S  Mapname '%S'\n"
            "%S  Chromosomename '%S'\n"
            "%S  Position '%S'\n"
            "%S  Lodscore %f\n"
            "%S  Use %u\n",
            indent, mml,
            indent, mml->Use,
            indent, mml->Markersynonym,
            indent, mml->Mapname,
            indent, mml->Chromosomename,
            indent, mml->Lodscore);

    ensMarkersynonymTrace(mml->Markersynonym, level + 1);

    ajStrDel(&indent);

    return ajTrue;
}
