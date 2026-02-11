slotChangeSkin()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QString strSkin = action->text();

    if (!strSkin.isEmpty())
    {
        if (strSkin.toLower() == "default" || strSkin.toLower() == "blue")
        {
            strSkin = strSkin.toLower();
            changeSkin(strSkin);
        }
        else
        {
            changeSkin(strSkin, false);
        }
    }

    m_skinName = strSkin;

    setCalendar();

    writeSetting();
}
