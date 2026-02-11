DoIsDestinationUsed( const gDestination * dest ) const
{
    return ( extrapolator_ && extrapolator_->IsDestinationUsed( dest ) ) || gCycleMovement::DoIsDestinationUsed( dest );
}
