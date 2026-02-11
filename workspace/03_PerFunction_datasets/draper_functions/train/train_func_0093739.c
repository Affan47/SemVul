keyPressEvent( QKeyEvent* keyEvent )
{
    LOG(logDEBUG4) << "keyPressEvent received";

    switch ( (keyEvent->text())[0].toAscii() ) {
        case '/':
            displayQuickFindBar( QuickFindMux::Forward );
            break;
        case '?':
            displayQuickFindBar( QuickFindMux::Backward );
            break;
        default:
            keyEvent->ignore();
    }

    if ( !keyEvent->isAccepted() )
        QSplitter::keyPressEvent( keyEvent );
}
