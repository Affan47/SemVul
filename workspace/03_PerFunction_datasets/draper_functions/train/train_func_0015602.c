option_number_name(option_number_ty o)
{
    switch (o)
    {
    case OPTION_ACTION:
        return "OPTION_ACTION";

    case OPTION_BOOK:
        return "OPTION_BOOK";

    case OPTION_CASCADE:
        return "OPTION_CASCADE";

    case OPTION_CMDFILE:
        return "OPTION_CMDFILE";

    case OPTION_DISASSEMBLE:
        return "OPTION_DISASSEMBLE";

    case OPTION_ERROK:
        return "OPTION_ERROK";

    case OPTION_FINGERPRINT:
        return "OPTION_FINGERPRINT";

    case OPTION_FINGERPRINT_WRITE:
        return "OPTION_FINGERPRINT_WRITE";

    case OPTION_FORCE:
        return "OPTION_FORCE";

    case OPTION_GATEFIRST:
        return "OPTION_GATEFIRST";

    case OPTION_IMPLICIT_ALLOWED:
        return "OPTION_IMPLICIT_ALLOWED";

    case OPTION_INCLUDE_COOKED:
        return "OPTION_INCLUDE_COOKED";

    case OPTION_INCLUDE_COOKED_WARNING:
        return "OPTION_INCLUDE_COOKED_WARNING";

    case OPTION_INGREDIENTS_FINGERPRINT:
        return "OPTION_INGREDIENTS_FINGERPRINT";

    case OPTION_INVALIDATE_STAT_CACHE:
        return "OPTION_INVALIDATE_STAT_CACHE";

    case OPTION_LOGGING:
        return "OPTION_LOGGING";

    case OPTION_METER:
        return "OPTION_METER";

    case OPTION_MKDIR:
        return "OPTION_MKDIR";

    case OPTION_PERSEVERE:
        return "OPTION_PERSEVERE";

    case OPTION_PRECIOUS:
        return "OPTION_PRECIOUS";

    case OPTION_REASON:
        return "OPTION_REASON";

    case OPTION_RECURSE:
        return "OPTION_RECURSE";

    case OPTION_SHALLOW:
        return "OPTION_SHALLOW";

    case OPTION_SILENT:
        return "OPTION_SILENT";

    case OPTION_STAR:
        return "OPTION_STAR";

    case OPTION_STRIP_DOT:
        return "OPTION_STRIP_DOT";

    case OPTION_TERMINAL:
        return "OPTION_TERMINAL";

    case OPTION_TOUCH:
        return "OPTION_TOUCH";

    case OPTION_UNLINK:
        return "OPTION_UNLINK";

    case OPTION_UPDATE:
        return "OPTION_UPDATE";

    case OPTION_UPDATE_MAX:
        return "OPTION_UPDATE_MAX";

    case OPTION_MATCH_MODE_REGEX:
        return "OPTION_MATCH_MODE_REGEX";

    case OPTION_TELL_POSITION:
        return "OPTION_TELL_POSITION";

    case OPTION_max:
        break;
    }
    return "option number unknown";
}
