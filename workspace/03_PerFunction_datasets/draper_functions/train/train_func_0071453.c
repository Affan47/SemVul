video_attach(const fn_call& fn)
{
    Video* video = ensure<IsDisplayObject<Video> >(fn);

    if (fn.nargs < 1) {
        IF_VERBOSE_ASCODING_ERRORS(
            log_aserror(_("attachVideo needs 1 arg"));
            );
        return as_value();
    }

    as_object* obj = toObject(fn.arg(0), getVM(fn));
    NetStream_as* ns;

    if (isNativeType(obj, ns)) {
		video->setStream(ns);
    } else {
        IF_VERBOSE_ASCODING_ERRORS(
            log_aserror(_("attachVideo(%s) first arg is not a NetStream instance"),
			fn.arg(0));
            );
    }
    return as_value();
}
