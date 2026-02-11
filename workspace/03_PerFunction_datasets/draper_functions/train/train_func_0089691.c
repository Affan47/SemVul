read_data(const char *input_string, const char *x_string_in) {
    istringstream in(input_string);

    delete xString;
    xString = 0;

    GB_ERROR error   = 0;
    int      version = -1;

    sec_assert(db->canDisplay());

    if (!error) {
        const char *string_buffer  = sec_read_line(in);
        double      firstLoopAngle = 0;

        error = sec_expect_keyword_and_ints(string_buffer, "VERSION", 7, &version, 0);
        if (error) {
            version = 2;

            int ignoreMaxIndex;
            error = sec_expect_keyword_and_ints(string_buffer, "MAX_INDEX", 9, &ignoreMaxIndex, 0);
            if (!error) {
                string_buffer = sec_read_line(in);
                error = sec_expect_keyword_and_doubles(string_buffer, "ROOT_ANGLE", 10, &firstLoopAngle, 0);
                if (error) {
                    firstLoopAngle += M_PI;
                    version = 1;
                    error   = 0;
                }
                else {
                    firstLoopAngle += M_PI;
                    string_buffer = sec_read_line(in);
                }
            }
        }
        else {
            if (version>DATA_VERSION) {
                error = GBS_global_string("Structure has version %i, your ARB can only handle versions up to %i", version, DATA_VERSION);
            }
            else {
                string_buffer = sec_read_line(in);
            }
        }

        if (!error) {
            sec_assert(!xString);

            size_t len     = strlen(x_string_in);
            size_t exp_len = db->length();

            if (len != exp_len && len != (exp_len+1)) {
                error = GBS_global_string("Wrong xstring-length (found=%zu, expected=%zu-%zu)",
                                          len, exp_len, exp_len+1);
            }
            else {
                xString = new XString(x_string_in, len, db->length());
#if defined(DEBUG)
                size_t xlen = xString->getLength();
                printf("x_string_in len=%zu\nxlen=%zu\nali_length=%zu\n", strlen(x_string_in), xlen, db->length());
#endif
            }
        }

        delete_root_loop();

        if (!error) {
#if defined(DEBUG)
            printf("Reading structure format (version %i)\n", version);
#endif

            if (strncmp(string_buffer, "LOOP={", 6) == 0) {
                SEC_loop *rootLoop = new SEC_loop(this);

                set_root_loop(rootLoop);
                set_under_construction(true);
                error = rootLoop->read(NULL, in, version, firstLoopAngle);

                if (!error) {
                    set_under_construction(false);
                }
                else {
                    delete_root_loop();
                }
            }
            else {
                error = GBS_global_string("Expected root loop ('LOOP={'), not '%s'", string_buffer);
            }
        }
    }

    if (!error) {
        if (version<DATA_VERSION) {
            printf("Converting secondary structure from version %i to %i\n", version, DATA_VERSION);
        }
        if (version<3) fixStructureBugs(version);
#if defined(CHECK_INTEGRITY)
        check_integrity(CHECK_STRUCTURE);
#endif
        if (version<3) {
            relayout();
            root_loop->fixAngleBugs(version);
        }
    }

    return error;
}
