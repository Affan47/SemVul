double_array_sum(double *array, int size)
{
    int i;
    double sum = 0.0;
    for (i = 0; i < size; i++) sum += array[i];
    return sum;
}
