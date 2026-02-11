_delayedForwardAnimation()
    {
        Q_Q( TextScrollingWidget );
        if( q->isUnderMouse() )
        {
            q->setText( text );
            q->startAnimation( QAbstractAnimation::Forward );
        }
    }
