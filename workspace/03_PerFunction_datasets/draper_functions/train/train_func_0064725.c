GetAllowedValues( TidyOption topt, const OptionDesc *d )
{
    if (d->vals)
    {
        tmbstr val = (tmbstr)malloc(1+strlen(d->vals));
        if (!val) outOfMemory();
        strcpy(val, d->vals);
        return val;
    }
    else
        return GetAllowedValuesFromPick( topt );
}
