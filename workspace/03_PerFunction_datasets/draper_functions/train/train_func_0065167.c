length()
{
    double sum = 0;
    for (int i=0;i<cols();i++)
    {
        sum += data[0][i] * data[0][i];
    }
    return sqrt(abs(sum));
}
