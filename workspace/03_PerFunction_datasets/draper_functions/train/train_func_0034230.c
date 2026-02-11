biasReplaced( Dynamic::BiasPtr oldBias, Dynamic::BiasPtr newBias )
{
    DEBUG_BLOCK;
    BiasPtr thisPtr( this );
    int index = m_biases.indexOf( oldBias );
    Q_ASSERT( index >= 0 );

    disconnect( oldBias.data(), 0, this, 0 );
    bool inModel = DynamicModel::instance()->index( thisPtr ).isValid();
    if( inModel )
        DynamicModel::instance()->beginRemoveBias( thisPtr, index );
    m_biases.removeAt( index );
    if( inModel )
        DynamicModel::instance()->endRemoveBias();
    emit biasRemoved( index );

    if( newBias )
    {
        connect( newBias.data(), SIGNAL(resultReady(Dynamic::TrackSet)),
                 this,  SLOT(resultReceived(Dynamic::TrackSet)) );
        connect( newBias.data(), SIGNAL(replaced(Dynamic::BiasPtr,Dynamic::BiasPtr)),
                 this, SLOT(biasReplaced(Dynamic::BiasPtr,Dynamic::BiasPtr)) );
        connect( newBias.data(), SIGNAL(changed(Dynamic::BiasPtr)),
                 this, SIGNAL(changed(Dynamic::BiasPtr)) );

        if( inModel )
            DynamicModel::instance()->beginInsertBias( thisPtr, index );
        m_biases.insert( index, newBias );
        if( inModel )
            DynamicModel::instance()->endInsertBias();


        emit biasAppended( newBias );
        emit biasMoved( m_biases.count()-1, index );
    }

    emit changed( thisPtr );
}
