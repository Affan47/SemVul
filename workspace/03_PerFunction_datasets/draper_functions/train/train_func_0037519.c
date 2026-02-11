partition_first_pivot(int* array, int length)
{
    int pivot = array[0];
    int i = 1;
    int j = 1;

    for (; j < length; j++) {
        if (array[j] < pivot) {
           swap(array, i, j);
           i++;
        }
    }
    swap(array, 0, i - 1);
    return i - 1;
}
