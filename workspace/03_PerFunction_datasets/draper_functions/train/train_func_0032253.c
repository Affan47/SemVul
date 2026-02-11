PrintAllowedValuesFromPick( TidyOption topt )
{
    TidyIterator pos = tidyOptGetPickList( topt );
    Bool first = yes;
    ctmbstr def;
    while ( pos )
    {
        if (first)
            first = no;
        else
            printf(", ");
        def = tidyOptGetNextPick( topt, &pos );
        printf("%s", def);
    }
}
