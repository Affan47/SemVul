load_image_file(const char* filename) {
    int retval;
    FILE* f;
    f = boinc_fopen(filename, "r");
    if (!f) goto done;
    fclose(f);


    present = true;
	retval = CreateTextureJPG(filename);
    if (!retval) {
        fprintf(stderr, "Successfully loaded '%s'.\n", filename);
        return 0;
    }
done:
    present = false;
    fprintf(stderr, "Failed to load '%s'.\n", filename);
    return -1;
}
