populateComboBox( QStringList results )
{
    QObject* query = sender();
    if( !query )
        return;

    QWeakPointer<KComboBox> combo = m_runningQueries.value(query);
    if( combo.isNull() )
        return;


    disconnect( combo.data(), 0, this, 0 );


    const QSet<QString> dataSet = results.toSet();
    QStringList dataList = dataSet.toList();
    dataList.sort();
    combo.data()->addItems( dataList );

    KCompletion* comp = combo.data()->completionObject();
    comp->setItems( dataList );


    combo.data()->setEditText( m_filter.value );
    connect( combo.data(), SIGNAL(editTextChanged(QString)),
            SLOT(valueChanged(QString)) );
}
