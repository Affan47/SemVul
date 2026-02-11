get_named_color (char * str, RGB * rgb ) {
    int i;
    for (i = 0; i <NUM_KNOWN_COLORS; i++) {
        if (strncmp(str, known_color_str[i],
                    strlen( known_color_str[i])) == 0){
            memcpy(rgb, &known_color_rgb[i], sizeof(RGB));
            return 1;
        }
    }
    printf("Did not recognize %s as a color; ignoring.\n", str);
    return 0;
}
