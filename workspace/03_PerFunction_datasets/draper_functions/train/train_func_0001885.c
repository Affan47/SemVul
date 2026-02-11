sortScores(vector<float>* scores, int f, int l)
{
    int i,last;

    if(f >= l)
        return;

    swap(scores, f, (f + l) / 2);
    last = f;
    for(i = f + 1; i <= l; i++)
    {
        if((*scores)[i] > (*scores)[f])
        {
            swap(scores, ++last, i);
        }
    }
    swap(scores, f, last);
    sortScores(scores, f, last - 1);
    sortScores(scores, last + 1, l);
}
