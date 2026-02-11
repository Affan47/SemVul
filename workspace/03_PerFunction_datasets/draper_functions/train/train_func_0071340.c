_removeAllRef(FWObject *rm)
{


    if (this == rm || this->isChildOf(rm)) return;

    for (FWObject::iterator i=begin(); i!=end(); i++)
        (*i)->_removeAllRef(rm);

    removeRef(rm);
}
