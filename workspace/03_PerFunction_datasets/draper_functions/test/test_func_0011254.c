setModalState(bool state)
{

    if (getModalState() == state)
        return;


    if (state)
    {
        activate();
        System::getSingleton().setModalTarget(this);
    }

    else
        System::getSingleton().setModalTarget(0);
}
