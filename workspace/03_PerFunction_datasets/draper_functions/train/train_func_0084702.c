sound_start(const fn_call& fn)
{
    IF_VERBOSE_ACTION (
    log_action(_("-- start sound"));
    )
    Sound_as* so = ensure<ThisIsNative<Sound_as> >(fn);
    int loop = 0;
    double secondOffset = 0;

    if (fn.nargs > 0) {
        secondOffset = toNumber(fn.arg(0), getVM(fn));

        if (fn.nargs > 1) {

            loop = std::max(0, toInt(fn.arg(1), getVM(fn)) - 1);
        }
    }
    so->start(secondOffset, loop);
    return as_value();
}
