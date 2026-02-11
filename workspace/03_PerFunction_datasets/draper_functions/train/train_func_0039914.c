loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    Q_UNUSED(errorMessage);
    bool result = m_image.load(imageFileName);
    if (result)
        m_imageFileName = imageFileName;
    return result;
}
