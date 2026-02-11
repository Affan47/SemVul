setRotation(DisplayObject& o, const as_value& val)
{

    const double rotation_val = toNumber(val, getVM(*getObject(&o)));


    if (isNaN(rotation_val)) {
        IF_VERBOSE_ASCODING_ERRORS(
        log_aserror(_("Attempt to set %s._rotation to %s "
            "(evaluating to number %g) refused"),
            o.getTarget(), val, rotation_val);
        );
        return;
    }
    o.set_rotation(rotation_val);
}
