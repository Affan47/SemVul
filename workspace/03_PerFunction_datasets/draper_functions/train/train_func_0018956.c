setPosition(int position)
{
    Link* link;
    int   i;

    if (position <= 1)
    {
	this->position = 1;
	this->next     = this->list->first;
    }
    else if (position >= this->list->size)
    {
	this->position = this->list->size;
	this->next     = this->list->last;
    }
    else
    {
	for (link = this->list->first, i = 1;
	     link AND i < position;
	     link = link->next, i++)
	    ;
	ASSERT(link);

	this->next     = link;
	this->position = position;
    }
}
