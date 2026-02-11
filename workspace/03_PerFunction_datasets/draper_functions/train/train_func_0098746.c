y
(
    size_t number
) const
{

    double result = 0;
    switch ( number % 4 )
    {
        case 0 : result = -5000;
                 break;
        case 1 : result = 5000;
                 break;
        case 2 : result = 5000;
                 break;
        case 3 : result = -5000;
                 break;
    }
    return result;
}
