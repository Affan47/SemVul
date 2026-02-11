evalDelete(const std::string& optarg)
{
    int rc = 0;
    switch (action_) {
    case Action::none:
        action_ = Action::erase;
        target_ = 0;

    case Action::erase:
        rc = parseCommonTargets(optarg, "erase");
        if (rc > 0) {
            target_ |= rc;
            rc = 0;
        }
        else {
            rc = 1;
        }
        break;
    default:
        std::cerr << progname() << ": "
                  << _("Option -d is not compatible with a previous option\n");
        rc = 1;
        break;
    }
    return rc;
}
