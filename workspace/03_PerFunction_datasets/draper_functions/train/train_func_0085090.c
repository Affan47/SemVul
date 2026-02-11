embed( QChar::Direction d, BidiState &bidi )
{
#if BIDI_DEBUG > 1
    qDebug("*** embed dir=%d emptyrun=%d", d, emptyRun );
#endif
    if ( d == QChar::DirPDF ) {
	BidiContext *c = bidi.context->parent;
	if (c) {
	    if ( bidi.eor != bidi.last ) {
		appendRun( bidi );
		bidi.eor = bidi.last;
	    }
	    appendRun( bidi );
	    emptyRun = true;
	    bidi.status.last = bidi.context->dir;
	    bidi.context->deref();
	    bidi.context = c;
	    if(bidi.context->override)
		dir = bidi.context->dir;
	    else
		dir = QChar::DirON;
	    bidi.status.lastStrong = bidi.context->dir;
	}
    } else {
	QChar::Direction runDir;
	if( d == QChar::DirRLE || d == QChar::DirRLO )
	    runDir = QChar::DirR;
	else
	    runDir = QChar::DirL;
	bool override;
	if( d == QChar::DirLRO || d == QChar::DirRLO )
	    override = true;
	else
	    override = false;

	unsigned char level = bidi.context->level;
	if ( runDir == QChar::DirR ) {
	    if(level%2)
		level += 2;
	    else
		level++;
	} else {
	    if(level%2)
		level++;
	    else
		level += 2;
	}

	if(level < 61) {
	    if ( bidi.eor != bidi.last ) {
                appendRun( bidi );
                bidi.eor = bidi.last;
            }
            appendRun( bidi );
            emptyRun = true;

	    bidi.context = new BidiContext(level, runDir, bidi.context, override);
	    bidi.context->ref();
	    dir = runDir;
	    bidi.status.last = runDir;
	    bidi.status.lastStrong = runDir;
	    bidi.status.eor = runDir;
	}
    }
}
