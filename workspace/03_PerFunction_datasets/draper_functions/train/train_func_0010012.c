keyPressEvent( QKeyEvent *e )
{
    int event_key = e->key() | e->modifiers();

    if ( KStandardShortcut::rotateUp().contains(event_key) )
        rotateUp();
    else if ( KStandardShortcut::rotateDown().contains(event_key) )
        rotateDown();
    else
        KComboBox::keyPressEvent( e );
}
