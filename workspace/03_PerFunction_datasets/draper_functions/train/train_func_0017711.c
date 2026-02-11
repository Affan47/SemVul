selectionChanged( int index )
{
    DEBUG_BLOCK;
    Q_ASSERT( m_biasSelection );

    QString biasName = m_biasSelection->itemData( index ).toString();

    Dynamic::BiasPtr oldBias( m_bias );
    Dynamic::BiasPtr newBias( Dynamic::BiasFactory::fromName( biasName ) );
    if( !newBias )
    {
        warning() << "Could not create bias with name:"<<biasName;
        return;
    }

debug() << "replace bias" << oldBias->toString() << "with" << newBias->toString();
    m_bias->replace( newBias );
debug() << "replaced";


    Dynamic::AndBias *oldABias = qobject_cast<Dynamic::AndBias*>(oldBias.data());
    Dynamic::AndBias *newABias = qobject_cast<Dynamic::AndBias*>(newBias.data());
    if( newABias ) {
        if( oldABias ) {
            for( int i = 0; i < oldABias->biases().count(); i++ )
            {
                newABias->appendBias( oldABias->biases()[i] );
            }
        }
        else
        {
            newABias->appendBias( oldBias );
        }
    }
}
