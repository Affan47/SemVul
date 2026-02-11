launch_crack(const char *dict_filename, const char *zip_filename)
{
    struct zc_pwdict *pwdict;
    struct zc_validation_data vdata[VDATA_ALLOC];
    size_t vdata_size;
    char pw[PW_BUF_LEN];
    int err;

    vdata_size = fill_validation_data(ctx, zip_filename,
                                      vdata, VDATA_ALLOC);
    if (vdata_size == 0)
        return EXIT_FAILURE;

    err = zc_pwdict_new_from_filename(ctx, dict_filename, &pwdict);
    if (err != 0)
        return EXIT_FAILURE;

    err = zc_pwdict_open(pwdict);
    if (err != 0) {
        zc_pwdict_unref(pwdict);
        return EXIT_FAILURE;
    }

    do {
        err = zc_pwdict_read_one_pw(pwdict, pw, PW_BUF_LEN);
        if (err == 0 && zc_crk_test_one_pw(pw, vdata, vdata_size)) {
            if (zc_file_test_password(zip_filename, pw)) {
                printf("Password is: %s\n", pw);
                break;
            }
        }
    } while (err == 0);

    zc_pwdict_close(pwdict);
    zc_pwdict_unref(pwdict);

    return 0;
}
