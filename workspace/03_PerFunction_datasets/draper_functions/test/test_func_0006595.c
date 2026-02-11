removeAction(Action* action)
{
    Q_ASSERT( action && ! action->objectName().isEmpty() );
    if( ! d->actionMap.contains(action->objectName()) ) {
        Q_ASSERT( ! d->actionList.contains(action) );
        return;
    }
    removeAction( action->objectName() );
}
