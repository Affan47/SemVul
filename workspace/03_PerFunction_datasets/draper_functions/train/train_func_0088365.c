data_dir_matches(ca_data_dir *d, const char*output_profile) {
        ca_assert(d);
        ca_assert(output_profile);


        if (!d->output_profile)
                return TRUE;

        return ca_streq(d->output_profile, output_profile);
}
