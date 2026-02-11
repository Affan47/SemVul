actionTriggered( QAction* action )
{
    emit fontSizeChanged( action->text().toInt() );
    KSelectAction::actionTriggered( action );
}
