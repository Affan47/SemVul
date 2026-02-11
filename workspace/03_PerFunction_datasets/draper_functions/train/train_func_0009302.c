favouriteClicked()
{
    Event event = Event::getById(mEventId, mConferenceId);

    QList<Event> conflicts = Event::conflictEvents(event.id(), mConferenceId);
    if(event.isFavourite())
    {
        event.setFavourite(false);
        favouriteButton->setIcon(QIcon(":/icons/favourite-off.png"));
    }
    else
    {
        event.setFavourite(true);
        favouriteButton->setIcon(QIcon(":/icons/favourite-on.png"));
    }
    event.update("favourite");

    if(event.isFavourite())
    {

        conflicts = Event::conflictEvents(event.id(), mConferenceId);
    }


    for(int i=0; i<conflicts.count(); i++)
        emit eventChanged(conflicts[i].id(), false);


    emit eventChanged(event.id(), true);
}
