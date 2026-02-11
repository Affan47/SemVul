findMedian(int *arr, const int &n)
{
    if (n < 1)
        throw std::invalid_argument("Empty array");
    if (n == 1)
        return *arr;
    std::sort(arr, arr + n);


    return arr[n / 2];
}
