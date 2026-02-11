Avatar(Account& pl, const std::string& entId) :
    m_account(pl),
    m_entityId(entId),
    m_entity(NULL),
    m_stampAtLastOp(TimeStamp::now()),
    m_lastOpTime(0.0),
    m_isAdmin(false)
{
    m_view = new View(this);
    m_entityAppearanceCon = m_view->Appearance.connect(sigc::mem_fun(this, &Avatar::onEntityAppear));

    m_router = new IGRouter(this);

    m_view->getEntityFromServer("");
    m_view->getEntity(m_entityId);
}
