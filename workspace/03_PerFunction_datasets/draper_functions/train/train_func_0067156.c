setupUi()
{
    ui.setupUi( this );

    addTracksToView();


    setWindowModality( Qt::ApplicationModal );


    struct NoProtection : QAbstractItemView
    {
        using QAbstractItemView::sizeHintForColumn;
    };

    int w = 0, desiredwidth = 0;
    for (int x = 0; x < ui.tracksWidget->columnCount(); ++x) {
        desiredwidth = reinterpret_cast<NoProtection*>(ui.tracksWidget)->sizeHintForColumn( x );
        w += desiredwidth;
    }

    ui.tracksWidget->setMinimumWidth( w );
    if (m_tracks.count() > 10)
        ui.tracksWidget->setMinimumHeight( ui.tracksWidget->sizeHint().height() * 2 );


    layout()->setSizeConstraint( QLayout::SetMinimumSize );

    int const W = QDesktopWidget().availableGeometry().width();
    if (sizeHint().width() > W)
        ui.tracksWidget->setMinimumWidth( W
                                          - (sizeHint().width() - ui.tracksWidget->width())
                                          - 10  );

    ui.tracksWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    ui.buttonBox->button( QDialogButtonBox::Ok )->setText( tr("Scrobble") );


    connect( ui.buttonBox, SIGNAL( accepted() ), SLOT( accept() ) );
    connect( ui.buttonBox, SIGNAL( rejected() ), SLOT( reject() ) );
    connect( ui.toggle,    SIGNAL( clicked() ),  SLOT( toggleChecked() ) );


    activateWindow();
}
