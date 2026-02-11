rcchk(int order, float rc1f[], float rc2f[])
{
    int i;

    for (i = 0;  i < order;  i++)
    {
        if (fabsf(rc2f[i]) > 0.99f)
        {
            for (i = 0;  i < order;  i++)
                rc2f[i] = rc1f[i];
            break;
        }
    }
    return 0;
}
