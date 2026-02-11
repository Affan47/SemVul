rowsInserted ( const QModelIndex & parent, int start, int end )
{
    Changing c = insert.pop();
    Q_ASSERT ( c.parent == parent );


    Q_ASSERT ( c.oldSize + ( end - start + 1 ) == model->rowCount ( parent ) );
    Q_ASSERT ( c.last == model->data ( model->index ( start - 1, 0, c.parent ) ) );

    if (c.next != model->data(model->index(end + 1, 0, c.parent))) {
        qDebug() << start << end;
        for (int i=0; i < model->rowCount(); ++i)
            qDebug() << model->index(i, 0).data().toString();
        qDebug() << c.next << model->data(model->index(end + 1, 0, c.parent));
    }

    Q_ASSERT ( c.next == model->data ( model->index ( end + 1, 0, c.parent ) ) );
}
