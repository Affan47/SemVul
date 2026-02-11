ChequerPosition(const int clockwise, const int point, const int chequer, int *px, int *py)
{

    int c_chequer;

    c_chequer = (!point || point == 25) ? 3 : 5;

    if (c_chequer > chequer)
        c_chequer = chequer;

    *px = positions[clockwise][point][0];
    *py = positions[clockwise][point][1] - (c_chequer - 1) * positions[clockwise][point][2];

}
