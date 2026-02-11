FindReplacement( const eCoord& coord, const eCoord& direction, const eCoord& lastDirection ) const
{

    tASSERT( !this->IsInGrid() );


    eFaceReplacementArgument arg;
    arg.coord = coord;
    arg.direction = direction;
    arg.lastDirection = lastDirection;


    return se_FindBestReplacement( this, arg ).first;
}
