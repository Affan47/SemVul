dlhash(Key key)
{
    DLKeyP dlkey = (DLKeyP)key;
    int a;
    long l;

    switch(dlkey->approx)
    {
	case approx_none:  a = 0; break;
	case approx_flat:  a = 1; break;
	case approx_lines: a = 2; break;
	case approx_dots:  a = 3; break;
	default:           a = 4; break;
    }

    l = (((dlkey->tag ^ a) ^ dlkey->density) ^
			(*(int *)&dlkey->linewidth)) ^ (dlkey->aalines*29);

    return (PseudoKey)l;
}
