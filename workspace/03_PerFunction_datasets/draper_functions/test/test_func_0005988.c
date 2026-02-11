mousePressEvent( QMouseEvent* e )
{
    if  ( (e->button() == Qt::LeftButton ||
           e->button() == Qt::MidButton ) &&
          d->clearButton ) {
        d->clickInClear = ( d->clearButton == childAt(e->pos()) || d->clearButton->underMouse() );

        if ( d->clickInClear ) {
            d->possibleTripleClick = false;
        }
    }

    if ( e->button() == Qt::LeftButton && d->possibleTripleClick ) {
        selectAll();
        e->accept();
        return;
    }


    if ( e->button() == Qt::MidButton ) {
        if ( hasSelectedText() && !isReadOnly() ) {
            if ( QApplication::clipboard()->text( QClipboard::Selection ).length() >0 ) {
                backspace();
            }
        }
    }

    QLineEdit::mousePressEvent( e );
}
