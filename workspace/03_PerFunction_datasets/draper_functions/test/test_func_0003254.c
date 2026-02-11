issmaller_int(void* current, void* given)
{
    int cur = ((Data_int)current)->num;
    int giv = ((Data_int)given)->num;
    if (cur < giv)
        return 1;
    else
        return 0;
}
