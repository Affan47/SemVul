mapAction (QSignalMapper * mapper, const QString & name,
		const QString & text, const Qt::Key key, SingmasterMove mapping)
{
    KAction * a;
    a = actionCollection()->addAction (name);
    a->setText (text);
    a->setShortcut (key);
    connect (a, SIGNAL (triggered(bool)), mapper, SLOT (map()));
    mapper->setMapping (a, mapping);
    return a;
}
