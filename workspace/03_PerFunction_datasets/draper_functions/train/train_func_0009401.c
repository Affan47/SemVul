xml_status(const fn_call& fn)
{
    XML_as* ptr = ensure<ThisIsNative<XML_as> >(fn);

    if (!fn.nargs) {
        return as_value(ptr->status());
    }

    if (fn.arg(0).is_undefined()) {
        return as_value();
    }

    const double status = toNumber(fn.arg(0), getVM(fn));
    if (isNaN(status) ||
            status > std::numeric_limits<boost::int32_t>::max() ||
            status < std::numeric_limits<boost::int32_t>::min()) {

        ptr->setStatus(static_cast<XML_as::ParseStatus>(
                    std::numeric_limits<boost::int32_t>::min()));
    }
    else ptr->setStatus(static_cast<XML_as::ParseStatus>(int(status)));
    return as_value();
}
