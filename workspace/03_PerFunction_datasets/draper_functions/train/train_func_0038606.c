mouseReleaseEvent( QMouseEvent* e )
{
    if ( d->clickInClear ) {
        if ( d->clearButton == childAt(e->pos()) || d->clearButton->underMouse() ) {
            QString newText;
            if ( e->button() == Qt::MidButton ) {
                newText = QApplication::clipboard()->text( QClipboard::Selection );
                setText( newText );
            } else {
                setSelection(0, text().size());
                del();
                emit clearButtonClicked();
            }
            emit textChanged( newText );
        }

        d->clickInClear = false;
        e->accept();
        return;
    }

    QLineEdit::mouseReleaseEvent( e );

    if (QApplication::clipboard()->supportsSelection() ) {
        if ( e->button() == Qt::LeftButton ) {

            copySqueezedText( false );
        }
    }
}
