biasChanged()
{
    emit changed( this );
    bool inModel = DynamicModel::instance()->index( this ).isValid();
    if( inModel )
        DynamicModel::instance()->biasChanged( m_bias );
}
