init(const RootEntity& ge, bool fromCreateOp)
{

    sight(ge);

    if (fromCreateOp)
    {
        m_recentlyCreated = true;
        new Alarm(5000, sigc::mem_fun(this, &Entity::createAlarmExpired));
    }
}
