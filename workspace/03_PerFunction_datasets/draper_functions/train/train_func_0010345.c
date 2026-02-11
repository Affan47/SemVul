remove(DcmObject *elem)
{
    errorFlag = EC_IllegalCall;
    if (!elementList->empty() && elem != NULL)
    {
        DcmObject *dO;
        elementList->seek(ELP_first);
        do {
            dO = elementList->get();
            if (dO == elem)
            {
                elementList->remove();
                elem->setParent(NULL);
                errorFlag = EC_Normal;
                break;
            }
        } while (elementList->seek(ELP_next));
    }
    if (errorFlag == EC_IllegalCall)
        return NULL;
    else
        return OFstatic_cast(DcmElement *, elem);
}
