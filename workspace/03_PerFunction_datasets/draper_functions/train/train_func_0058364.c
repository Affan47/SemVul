addGGapsMask(vector<char>* mask, int len, vector<int>* path1,
                                           vector<int>* path2)
{
    int i, ix;
    char *ta;

    ta = new char[len + 1];

    ix = 0;
    if (switchProfiles == false)
    {
        for (i = 0; i < len; i++)
        {
            if ((*path1)[i] == 2)
            {
                ta[i] = (*mask)[ix];
                ix++;
            }
            else if ((*path1)[i] == 1)
            {
                ta[i] = _gapPos1;
            }
        }
    }
    else
    {
        for (i = 0; i < len; i++)
        {
            if ((*path2)[i] == 2)
            {
                ta[i] = (*mask)[ix];
                ix++;
            }
            else if ((*path2)[i] == 1)
            {
                ta[i] = _gapPos1;
            }
        }
    }
    mask->resize(len + 2);

    for (i = 0; i < len; i++)
    {
        (*mask)[i] = ta[i];
    }


    delete [] ta;
    ta  = NULL;
}
