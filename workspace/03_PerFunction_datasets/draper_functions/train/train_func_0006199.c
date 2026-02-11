operator!=(const CL_Vector2& rkVector) const
{
    if ( FUZZ == 0.0f )
        return x != rkVector.x || y != rkVector.y;
    else
        return fabs(x-rkVector.x) > FUZZ || fabs(y-rkVector.y) > FUZZ;
}
