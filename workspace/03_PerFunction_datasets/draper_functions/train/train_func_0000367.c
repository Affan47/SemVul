orderBy( qint64 value, bool descending )
{
    d->orderByField = value;
    d->orderDescending = descending;
    switch( value )
    {
        case Meta::valYear:
        case Meta::valDiscNr:
        case Meta::valTrackNr:
        case Meta::valScore:
        case Meta::valRating:
        case Meta::valPlaycount:
        case Meta::valFilesize:
        case Meta::valSamplerate:
        case Meta::valBitrate:
        case Meta::valLength:
        {
            d->orderByNumberField = true;
            break;
        }


        default:
            d->orderByNumberField = false;
    }
    return this;
}
