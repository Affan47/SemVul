sound_loadsound(const fn_call& fn)
{
    Sound_as* so = ensure<ThisIsNative<Sound_as> >(fn);

    if (!fn.nargs) {
        IF_VERBOSE_ASCODING_ERRORS(
        log_aserror(_("Sound.loadSound() needs at least 1 argument"));
            );
        return as_value();
    }

    std::string url = fn.arg(0).to_string();

    bool streaming = false;
    if ( fn.nargs > 1 ) {
        streaming = toBool(fn.arg(1), getVM(fn));

        IF_VERBOSE_ASCODING_ERRORS(
        if ( fn.nargs > 2 )
        {
            std::stringstream ss; fn.dump_args(ss);
            log_aserror(_("Sound.loadSound(%s): arguments after first 2 "
                    "discarded"), ss.str());
        }
        );
    }

    so->loadSound(url, streaming);

    return as_value();
}
