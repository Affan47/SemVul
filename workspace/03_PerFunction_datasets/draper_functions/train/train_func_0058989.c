Size() const
{
    unsigned int result = argumentCurrent_ - data_;
    if( IsMessageInProgress() ){


        result += RoundUp4( (end_ - typeTagsCurrent_) + 2 );
    }

    return result;
}
