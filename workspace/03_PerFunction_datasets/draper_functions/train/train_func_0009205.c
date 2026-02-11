LogCube(const int n)
{

    int i;

    for (i = 0;; i++)
        if (n <= (1 << i))
            return i;
}
