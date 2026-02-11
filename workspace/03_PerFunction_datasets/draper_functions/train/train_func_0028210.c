point_polar(const fn_call& fn)
{

    as_value lval;
    as_value aval;

    if ( fn.nargs )
    {
        lval=fn.arg(0);
        if ( fn.nargs > 1 ) aval=fn.arg(1);
        else
        {
            IF_VERBOSE_ASCODING_ERRORS(
            std::stringstream ss; fn.dump_args(ss);
            log_aserror(_("Point.polar(%s): %s"), ss.str(),
                        _("missing arguments"));
            );
        }
    }
    else
    {
        IF_VERBOSE_ASCODING_ERRORS(
        std::stringstream ss; fn.dump_args(ss);
        log_aserror(_("Point.polar(%s): %s"), ss.str(), _("missing arguments"));
        );
    }

    double len = toNumber(lval, getVM(fn));
    double angle = toNumber(aval, getVM(fn));

    double x = len * std::cos(angle);
    double y = len * std::sin(angle);

    as_value xval(x);
    as_value yval(y);
    return constructPoint(fn, x, y);
}
