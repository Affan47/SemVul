MG_expect_renamed() {
    GB_ERROR error = 0;
    if (!was_renamed) error = "First you have to rename species in both databases";
    return error;
}
