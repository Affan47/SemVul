R3InitShapes(void)
{

    if ((R3shapes_active_count++) > 0) return TRUE;


    if (!R2InitShapes()) return FALSE;


    if (!R3InitCircle()) return FALSE;


    return TRUE;
}
