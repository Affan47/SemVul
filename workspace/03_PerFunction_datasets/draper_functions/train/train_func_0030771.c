isSlaveOnHoldFor(const KUrl& url)
{
    if (url.isValid() && m_urlOnHold.isValid() && url == m_urlOnHold)
        return true;

    return Slave::checkForHeldSlave(url);
}
