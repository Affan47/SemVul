dropMimeData(const QMimeData *data,
                                    Qt::DropAction action,
                                    int row, int column, const QModelIndex &_parent)
{
    Q_UNUSED( column );

    QModelIndex parent = _parent;

    if( action == Qt::IgnoreAction )
        return true;

    if( data->hasFormat("application/amarok.biasModel.index") )
    {

        QByteArray bytes = data->data("application/amarok.biasModel.index");
        QDataStream stream( &bytes, QIODevice::ReadOnly );
        QModelIndex index = unserializeIndex( &stream );

        if( !index.isValid() )
            return false;

        QObject* o = static_cast<QObject*>(index.internalPointer());
        BiasedPlaylist* indexPlaylist = qobject_cast<BiasedPlaylist*>(o);
        BiasPtr indexBias( qobject_cast<Dynamic::AbstractBias*>(o) );


        if( indexPlaylist )
        {
            while( parent.isValid() )
            {
                row = parent.row() + 1;
                column = parent.column();
                parent = parent.parent();
            }
        }

debug() << "dropMimeData action" << action;


        if( action == Qt::CopyAction )
        {

            if( indexPlaylist )
            {
                insertPlaylist( row, cloneList( indexPlaylist ) );
                return true;
            }

            else if( indexBias )
            {
                insertBias( row, parent, cloneBias( indexBias ) );
                return true;
            }
        }
        else if( action == Qt::MoveAction )
        {

            if( indexPlaylist )
            {
                insertPlaylist( row, indexPlaylist );
                return true;
            }

            else if( indexBias )
            {
                indexBias->replace( Dynamic::BiasPtr() );
                insertBias( row, parent, Dynamic::BiasPtr(indexBias) );
                return true;
            }
        }
    }

    return false;
}
