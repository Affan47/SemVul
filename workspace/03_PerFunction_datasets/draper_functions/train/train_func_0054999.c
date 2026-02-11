createWidget(QWidget* parent)
{
    kDebug(129) << "KFontAction::createWidget()";
#ifdef __GNUC__
#warning FIXME: items need to be converted
#endif


    KFontComboBox *cb = new KFontComboBox( parent );
    cb->setFontList(items());

    kDebug(129) << "\tset=" << font();

    cb->setCurrentFont( QFont( font().toLower() ) );
    kDebug(129) << "\tspit back=" << cb->currentFont().family();

    connect( cb, SIGNAL(currentFontChanged(QFont)), SLOT(_k_slotFontChanged(QFont)) );
    cb->setMinimumWidth( cb->sizeHint().width() );
    return cb;
}
