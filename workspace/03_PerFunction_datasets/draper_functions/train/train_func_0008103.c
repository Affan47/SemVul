AddDestination( gDestination * dest )
{


    dest->InsertIntoList(&destinationList);


    if (dest->next && dest->next->hasBeenUsed){
        delete dest;
        return;
    }

    this->NotifyNewDestination( dest );


    dest->InsertIntoList(&destinationList);
}
