slotRehighlight()
{
    kDebug(0) << "KDictSpellingHighlighter::slotRehighlight()";
    if (d->completeRehighlightRequired) {
	rehighlight();
    } else {
	int para, index;
	textEdit()->getCursorPosition( &para, &index );

	textEdit()->insertAt( "", para, index );
    }
    if (d->checksDone == d->checksRequested)
	d->completeRehighlightRequired = false;
    QTimer::singleShot( 0, this, SLOT(slotAutoDetection()));
}
