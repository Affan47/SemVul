distort_sanitize_args(DistortArgs *args)
{
    args->interp = gwy_enum_sanitize_value(args->interp,
                                           GWY_TYPE_INTERPOLATION_TYPE);
    args->exterior = CLAMP(args->exterior,
                           GWY_EXTERIOR_BORDER_EXTEND,
                           GWY_EXTERIOR_FIXED_VALUE);
    args->update = !!args->update;
}
