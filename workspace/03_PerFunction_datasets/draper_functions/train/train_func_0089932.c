permute_array(key_t *array, int count)
{
    int i, j;
    key_t tmp;

    srand(100);
    for (i=0; i < count; i++)
    {
        j = i + (random() % (count - i));
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}
