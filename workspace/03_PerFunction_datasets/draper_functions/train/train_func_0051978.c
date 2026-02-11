space_scale(char e)
{
    int scale;
    switch (e) {
        case 'g':
            scale = 1000 * 1000 * 1000;
            break;
        case 'G':
            scale = 1024 * 1024 * 1024;
            break;
        case 'm':
            scale = 1000 * 1000;
            break;
        case 'M':
            scale = 1024 * 1024;
            break;
        case 'k':
            scale = 1000;
            break;
        case 'K':
            scale = 1024;
            break;
        default:
            if (e != '\0') {
                fprintf(stderr, "unknown modifier for space: %c\n", e);
                exit(EXIT_FAILURE);
            }
            scale = 1;
            break;
    }
    return scale;
}
