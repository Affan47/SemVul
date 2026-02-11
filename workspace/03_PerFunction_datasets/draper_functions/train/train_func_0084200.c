__swap(AV* av, int i, int j)
{
    IV tmp = GETIV(av, i);
    SETIV(av, i, GETIV(av, j));
    SETIV(av, j, tmp);
}
