ChangeColorOrder(const int sorttype, const int ix0, const int ix1)
{
    QRadialGradient tmp = mGradMap[ix0];

    if (sorttype == 1)
    {
        mGradMap[ix0] = mGradMap[ix1];
    }
    else
    {
        int step = (ix1 > ix0) ? 1 : -1;
        int i;
        for (i = ix0;; i += step)
        {
            mGradMap[i] = mGradMap[i + step];
            if (i == ix1 - step)
            {
                break;
            }
        }
    }

    mGradMap[ix1] = tmp;
}
