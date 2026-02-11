percentId(vector<int>* s1, vector<int>* s2)
{
    int i;
    int count, total;
    float score;

    count = total = 0;
    for (i = 0; i < prfLength; i++)
    {
        if (((*s1)[i] >= 0) && ((*s1)[i] < userParameters->getMaxAA()))
        {
            total++;
            if ((*s1)[i] == (*s2)[i])
            {
                count++;
            }
        }
        if ((*s1)[i]==(-3) || (*s2)[i]==(-3))
        {
            break;
        }

    }

    if(total == 0)
    {
        score = 0;
    }
    else
    {
        score = 100.0 * (float)count / (float)total;
    }
    return (score);
}
