sharedobject_flush(const fn_call& fn)
{
    GNASH_REPORT_FUNCTION;

    SharedObject_as* obj = ensure<ThisIsNative<SharedObject_as> >(fn);

    IF_VERBOSE_ASCODING_ERRORS(
        if (fn.nargs > 1)
        {
            std::ostringstream ss;
            fn.dump_args(ss);
            log_aserror(_("Arguments to SharedObject.flush(%s) will be "
                    "ignored"), ss.str());
        }
    );

    int space = 0;
    if (fn.nargs) {
        space = toInt(fn.arg(0), getVM(fn));
    }


    if (!obj->data()) return as_value();


    return as_value(obj->flush(space));
}
