breakMove()
{
    breakThinking = true;
    playing = false;

    for(std::list<View*>::iterator i = views.begin(); i != views.end(); i++)
        (*i)->breakMove();
}
