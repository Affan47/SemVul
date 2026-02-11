Conv_ALint_ALfloat(ALfloat val)
{
    if(val > 1.0f) return 2147483647;
    if(val < -1.0f) return -2147483647-1;
    return (ALint)(val * 2147483647.0);
}
