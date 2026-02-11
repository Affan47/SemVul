get_dimensions(long *dim, long *entries, FILE *input_file) {
    int count = fscanf(input_file, "%ld %ld", dim, entries);
    if(count != 2) {
        perror("The input file does not state the dimension and number of entries on the first line.\n");
    }
}
