createNewFolder(const QString & name, KBookmark parent)
{
    if(!m_layout)
        initLayoutPrivate();
    if(parent.isNull())
        parent = m_mgr->root();
    setButtons( Ok | Cancel );
    setButtonGuiItem( KDialog::Ok, KStandardGuiItem::ok() );
    setCaption( i18nc("@title:window","New Folder"));
    m_url->setVisible(false);
    m_urlLabel->setVisible(false);
    m_comment->setVisible(true);
    m_commentLabel->setVisible(true);
    m_comment->setText(QString());
    m_title->setText(name);
    setParentBookmark(parent);
    m_folderTree->setVisible(true);

    m_mode = NewFolder;
    aboutToShow(m_mode);

    if(exec() == QDialog::Accepted)
        return m_bm.toGroup();
    else
        return KBookmarkGroup();
}
