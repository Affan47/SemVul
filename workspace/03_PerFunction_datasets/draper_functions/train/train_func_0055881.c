endSync(bool success)
{
    m_sub->endSubSync(success);


    if (success) {
        string updatedRevision = m_sub->subDatabaseRevision();
        m_metaNode->setProperty("databaseRevision", updatedRevision);


        m_trackingNode->clear();
        BOOST_FOREACH(const SubRevisionMap_t::value_type &entry,
                      m_revisions) {
            const std::string &mainid = entry.first;
            const SubRevisionEntry &ids = entry.second;
            std::stringstream buffer;
            buffer << '/' << m_escape.escape(ids.m_revision) << '/';
            buffer << m_escape.escape(ids.m_uid) << '/';
            BOOST_FOREACH(const std::string &subid, ids.m_subids) {
                buffer << m_escape.escape(subid) << '/';
            }
            m_trackingNode->setProperty(mainid, buffer.str());
        }


        m_trackingNode->flush();
        m_metaNode->flush();
    } else {


    }


    return "1";


}
