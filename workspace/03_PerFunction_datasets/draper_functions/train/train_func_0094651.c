fix_year(int y)
{

    if (y < 70)
        return (y + 2000);


    if (y > 19000)
        return (1900 + (y - 19000));


    if (y < 1902)
        return (y + 1900);


    return y;
}
