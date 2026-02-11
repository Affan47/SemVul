findCompletion( const QString& string )
{
    QChar ch;
    QString completion;
    const KCompTreeNode *node = d->myTreeRoot;


    for( int i = 0; i < string.length(); i++ ) {
        ch = string.at( i );
        node = node->find( ch );

        if ( node )
            completion += ch;
        else
            return QString();
    }


    while ( node->childrenCount() == 1 ) {
        node = node->firstChild();
        if ( !node->isNull() )
            completion += *node;
    }


    if ( node && node->childrenCount() > 1 ) {
        d->myHasMultipleMatches = true;

        if ( d->myCompletionMode == KGlobalSettings::CompletionAuto ) {
            d->myRotationIndex = 1;
            if (d->myOrder != Weighted) {
                while ( (node = node->firstChild()) ) {
                    if ( !node->isNull() )
                        completion += *node;
                    else
                        break;
                }
            }
            else {


                const KCompTreeNode* temp_node = 0L;
                while(1) {
                    int count = node->childrenCount();
                    temp_node = node->firstChild();
                    uint weight = temp_node->weight();
                    const KCompTreeNode* hit = temp_node;
                    for( int i = 1; i < count; i++ ) {
                        temp_node = node->childAt(i);
                        if( temp_node->weight() > weight ) {
                            hit = temp_node;
                            weight = hit->weight();
                        }
                    }

                    if ( hit->isNull() )
                        break;

                    node = hit;
                    completion += *node;
                }
            }
        }

        else
            doBeep( PartialMatch );
    }

    return completion;
}
