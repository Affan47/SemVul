calc_abs_angle() const {
    sec_assert(!abs_angle_valid);

    const SEC_base *previous = parent();
    if (previous) {
#if defined(DEBUG)
        static int avoid_deep_recursion = 0;
        avoid_deep_recursion++;
        sec_assert(avoid_deep_recursion<1000);
#endif

        abs_angle = previous->get_abs_angle()+rel_angle;

#if defined(DEBUG)
        avoid_deep_recursion--;
#endif
    }
    else {
        abs_angle = rel_angle;
    }
    abs_angle_valid = true;

    return abs_angle;
}
