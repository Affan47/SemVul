ftoa( t_CKFLOAT val, t_CKUINT precision )
{
    char str[32];
    char buffer[128];
    if( precision > 32 ) precision = 32;
    sprintf( str, "%%.%lif", precision );
    sprintf( buffer, str, val );
    return string(buffer);
}
