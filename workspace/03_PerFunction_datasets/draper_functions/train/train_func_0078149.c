read(istream & in, int version, double& old_angle_in) {
    const char *string_buffer = sec_read_line(in);
    GB_ERROR    error         = 0;

    old_angle_in = NAN;

    if (version >= 3) {
        double angle;

        error = sec_expect_keyword_and_doubles(string_buffer, "REL", 3, &angle, 0);

        if (!error) {
            string_buffer = sec_read_line(in);
            set_rel_angle(angle);
        }
    }
    else {
        double angle;

        error = sec_expect_keyword_and_doubles(string_buffer, "DELTA", 5, &angle, 0);
        if (!error) {
            string_buffer = sec_read_line(in);
            set_abs_angle(angle);

            if (version == 2) {
                error = sec_expect_keyword_and_doubles(string_buffer, "DELTA_IN", 8, &angle, 0);

                if (!error) {
                    string_buffer = sec_read_line(in);
                    old_angle_in  = angle+M_PI;
                }
            }
            else {
                old_angle_in = angle;
            }
        }
    }

    if (!error) error = sec_expect_constraints(string_buffer, "LENGTH", 6, this);

    return error;
}
