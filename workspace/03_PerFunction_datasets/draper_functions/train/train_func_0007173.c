S_BlowHoles( eWall * w )
{

    eCoord normal = w->Vec().Conj();
    normal.Normalize();

    eCoord Pos1 = normal.Turn( w->EndPoint(0) - s_explosionCoord );
    eCoord Pos2 = normal.Turn( w->EndPoint(1) - s_explosionCoord );

    tASSERT( fabs( Pos1.y - Pos2.y ) <= fabs( Pos1.y + Pos2.y + .1f ) * .1f );

    REAL alpha = .5f;
    if ( Pos1.x != Pos2.x)
        alpha = Pos1.x / ( Pos1.x - Pos2.x );

    REAL radius = s_explosionRadius * s_explosionRadius - Pos1.y * Pos2.y;


    if ( radius < 0 )
        return;

    radius = sqrt( radius );


    gPlayerWall* wall = dynamic_cast<gPlayerWall*>( w );
    if ( ! wall )
        return;

    REAL closestPos = wall->Pos( alpha );

    REAL start = closestPos - radius;
    REAL end = closestPos + radius;


    REAL wallEnd = wall->EndPos();
    REAL wallBeg = wall->BegPos();
    if ( wallEnd <= wallBeg )
    {
        return;
    }
    REAL endAlpha = ( end - wallBeg ) / ( wallEnd - wallBeg );

    clamp01( endAlpha );
    REAL endHoleTime = wall->Time( endAlpha );
    if ( endHoleTime > s_explosionTime )
    {
        REAL begTime = wall->BegTime();
        REAL endTime = wall->EndTime();
        REAL timeNorm = endTime - begTime;
        if ( timeNorm != 0.0f )
        {
            endAlpha = ( s_explosionTime - begTime ) / timeNorm;
            end = wall->Pos( endAlpha );
        }
    }

    if ( end > start )
    {
        wall->BlowHole ( start, end, s_holer );
    }
}
