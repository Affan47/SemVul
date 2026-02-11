main(int argc, char *argv[]) {
    if (argc < 2)
        die("USAGE: ex18 5 2 1 6 3 4");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers)
        die("Memory error");

    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    puts("BUBBLE SORT");
    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, bubble_sort, strange_order);

    puts("INSERTION SORT");
    test_sorting(numbers, count, insertion_sort, sorted_order);
    test_sorting(numbers, count, insertion_sort, reverse_order);
    test_sorting(numbers, count, insertion_sort, strange_order);

    free(numbers);

    return 0;
}
