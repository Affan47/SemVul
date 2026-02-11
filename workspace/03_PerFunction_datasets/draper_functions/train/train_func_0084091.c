setX(DisplayObject& o, const as_value& val)
{

    const double newx = toNumber(val, getVM(*getObject(&o)));


    if (isNaN(newx))
    {
        IF_VERBOSE_ASCODING_ERRORS(
        log_aserror(_("Attempt to set %s._x to %s "
            "(evaluating to number %g) refused"),
            o.getTarget(), val, newx);
        );
        return;
    }

    SWFMatrix m = getMatrix(o);

    m.set_x_translation(pixelsToTwips(infinite_to_zero(newx)));
    o.setMatrix(m);
    o.transformedByScript();
}
