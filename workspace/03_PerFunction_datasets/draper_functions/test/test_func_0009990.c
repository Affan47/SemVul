width() const
{
    if (!isValid())
        return qQNaN();

    double result = d_ptr->bottomRight.longitude() - d_ptr->topLeft.longitude();
    if (result < 0.0)
        result += 360.0;
    if (result > 360.0)
        result -= 360.0;

    return result;
}
