test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;

    int *sorted = bubble_sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested");


    for(i = 0; i < count; i++) {
        printf("%d", sorted[i]);
    }
    printf("\n");

    free(sorted);


    unsigned char *data = (unsigned char *)cmp;

    for(i = 0; i < 25; i++) {
        printf("%02x:", data[i]);
    }
    printf("\n");
}
