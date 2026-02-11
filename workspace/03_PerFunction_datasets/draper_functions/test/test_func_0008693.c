sort_and_count_inversions(int* array, int length)
{
    if (length == 1) return 0;

    int* left = array;
    int left_length = length / 2;
    int* right = array + left_length;
    int right_length = length - left_length;

    return sort_and_count_inversions(left,  left_length) +
           sort_and_count_inversions(right, right_length) +
           merge_and_split_count_inversions (left,  left_length,
                                             right, right_length,
                                             array, length);
}
