vocisect(objnum *list1, objnum *list2)
{
    int i, j, k;

    for (i = k = 0 ; list1[i] != MCMONINV ; ++i)
    {
        for (j = 0 ; list2[j] != MCMONINV ; ++j)
        {
            if (list1[i] == list2[j])
            {
                list1[k++] = list1[i];
                break;
            }
        }
    }
    list1[k] = MCMONINV;
    return(k);
}
