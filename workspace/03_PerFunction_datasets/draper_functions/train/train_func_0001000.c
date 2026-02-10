setAlpha( gfloat alpha )
{
    g_return_if_fail( ( 0.0 <= alpha ) && ( alpha <= 1.0 ) );
    setColorAlpha( _color, alpha );
}
