moviecliploader_unloadClip(const fn_call& fn)
{
    if (!fn.nargs) {
		IF_VERBOSE_ASCODING_ERRORS(
            std::stringstream ss; fn.dump_args(ss);
            log_aserror(_("MovieClipLoader.unloadClip(%s): expected at least"
                    " one argument"), ss.str());
        );
        return as_value();
    }

    const std::string filespec = fn.arg(0).to_string();
    log_unimpl(_("MovieClipLoader.unloadClip: %s"), __PRETTY_FUNCTION__, filespec);
    return as_value();
}
