buildDisplay() {

        foreach( QWidget* w, wl )
            delete w;
        wl.clear();


        if ( QLayoutItem* item = layout->takeAt( 0 ) )
            delete item;


        for( QStringList::const_iterator it = tags.constBegin();
             it != tags.constEnd(); ++it ) {
            if (  it != tags.constBegin() ) {
                QLabel* label = new QLabel( "-", parent );
                wl.append( label );
                layout->addWidget( label );
            }
            KUrlLabel* label = new KUrlLabel( *it, *it, parent );
            wl.append( label );
            label->setUnderline( false );
            layout->addWidget( label );

            connect( label, SIGNAL(leftClickedUrl(QString)),
                     parent, SIGNAL(tagClicked(QString)) );
        }

        layout->addStretch( 1 );
    }
