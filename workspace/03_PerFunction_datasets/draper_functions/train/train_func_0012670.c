load_file(hashmap *map, char *filename) {
    FILE *file = 0;
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    load_properties(map, file);
    fclose(file);
}
