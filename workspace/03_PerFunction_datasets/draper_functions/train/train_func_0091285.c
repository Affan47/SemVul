_dxf_ExDictionaryBeginIterate (EXDictionary d)
{
    if (!d)
	return (OK);

    DICT_LOCK (d->locking, d);

    d->iterIndex = -1;
    d->iterItem = NULL;

    return (OK);
}
