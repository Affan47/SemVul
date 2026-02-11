glk_current_simple_time(glui32 factor)
{
    struct timeval tv;

    if (factor == 0) {
        gli_strict_warning("current_simple_time: factor cannot be zero.");
        return 0;
    }

    if (gettimeofday(&tv, NULL)) {
        gli_strict_warning("current_simple_time: gettimeofday() failed.");
        return 0;
    }

    return gli_simplify_time(tv.tv_sec, factor);
}
