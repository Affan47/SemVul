PushHoliday(
    holstorep_t hp,
    holstorep_t *lp
    )
{
    holstorep_t temp;

    temp = getHolstorep ();
    initStr (&temp->name, MAX_LINE_LEN);
    strcpy (temp->name, hp->name);
    temp->typeMask = hp->typeMask;

    if ( ! *lp )
        *lp = temp;
    else
    {
        temp->next = *lp;
        *lp = temp;
    }
    return temp->typeMask;
}
