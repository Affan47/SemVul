isAscending(const int anMove[8])
{
    if (anMove[0] < 0)
        return FALSE;

    if (anMove[0] != 24) {

        if (anMove[1] > -1)

            return anMove[0] < anMove[1];
        else
            return anMove[0] > 17;
    } else
        return anMove[1] < 6;
}
