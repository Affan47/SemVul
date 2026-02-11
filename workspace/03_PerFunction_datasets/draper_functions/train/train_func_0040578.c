avatarLogoutResponse(const RootOperation& op)
{
    if (!op->instanceOf(INFO_NO)) {
        warning() << "received an avatar logout response that is not an INFO";
        return;
    }

    const std::vector<Root>& args(op->getArgs());

    if (args.empty() || (args.front()->getClassNo() != LOGOUT_NO)) {
        warning() << "argument of avatar logout INFO is not a logout op";
        return;
    }

    RootOperation logout = smart_dynamic_cast<RootOperation>(args.front());
    const std::vector<Root>& args2(logout->getArgs());
    if (args2.empty()) {
        warning() << "argument of avatar logout INFO is logout without args";
        return;
    }

    std::string charId = args2.front()->getId();
    debug() << "got logout for character " << charId;

    if (!m_characterIds.count(charId)) {
        warning() << "character ID " << charId << " is unknown on account " << m_accountId;
    }

    ActiveCharacterMap::iterator it = m_activeCharacters.find(charId);
    if (it == m_activeCharacters.end()) {
        warning() << "character ID " << charId << " does not correspond to an active avatar.";
        return;
    }

    AvatarDeactivated.emit(it->second);
    delete it->second;
}
