joystick_long_config_name(const fs_ml_input_device *device) {
    const char *in = device->name;
    char *result = malloc(strlen(device->name) + 1);
    char *out = result;
    int other = 0;
    while (*in) {
#if 0
        if (!with_number) {
#endif
            if (*in == '#') {

                break;
            }
#if 0
        }
#endif
        char c = fs_ascii_tolower(*in);
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            if (other) {
                *(out++) = '_';
            }
            *(out++) = c;
            other = 0;
        }
        else {
            other = 1;
        }
        in++;
    }
    *out = '\0';
    if (fs_str_has_suffix(result, "_")) {
        result[strlen(result) - 1] = '\0';
    }

#if defined(WINDOWS)
    const char *platform = "windows";
#elif defined(MACOSX)
    const char *platform = "macosx";
#elif defined(LINUX)
    const char *platform = "linux";
#elif defined(FREEBSD)
    const char *platform = "freebsd";
#elif defined(OPENBSD)
    const char *platform = "openbsd";
#else
    const char *platform = "unknown";
#endif

    char *result2 = fs_strdup_printf("%s_%d_%d_%d_%d_%s", result,
            device->buttons, device->axes, device->hats, device->balls,
            platform);
    free(result);
    return result2;
}
