takeResource()
{

    if (m_cloudTaken) {
        qWarning("WordcloudContent::takeResource: resource already taken");
        return QVariant();
    }


    m_cloudTaken = true;
    Wordcloud::Cloud * cloud = m_cloud;
    m_cloud = 0;
    return qVariantFromValue((void *)cloud);
}
