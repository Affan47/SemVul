rating() const
{
    GET_TRACK
    return track ? track->statistics()->rating() : 0;
}
