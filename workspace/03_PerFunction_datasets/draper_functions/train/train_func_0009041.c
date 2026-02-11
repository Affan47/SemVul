subtract(const std::string &first, const std::string &second)
{
    if (MathLib::isInt(first) && MathLib::isInt(second)) {
        return toString(toLongNumber(first) - toLongNumber(second));
    }

    if (first == second)
        return "0.0" ;

    double d1 = toDoubleNumber(first);
    double d2 = toDoubleNumber(second);

    int count = 0;
    while (d1 > 100000.0 * d2 && toString(d1-d2)==first && ++count<5)
        d2 *= 10.0;
    while (d2 > 100000.0 * d1 && toString(d1-d2)==second && ++count<5)
        d1 *= 10.0;

    return toString(d1 - d2);
}
