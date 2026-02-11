findOrCreateSequenceItem(const DcmTag& seqTag,
                                              DcmItem *&item,
                                              const signed long itemNum)
{
    DcmStack stack;

    OFCondition status = search(seqTag, stack, ESM_fromHere, OFFalse );
    DcmSequenceOfItems *sequence = NULL;

    if (status.good())
    {

        DcmElement *delem = OFstatic_cast(DcmElement *, stack.top());
        if (delem != NULL)
        {

            if ((delem->ident() == EVR_SQ) || (delem->ident() == EVR_pixelSQ))
                sequence = OFstatic_cast(DcmSequenceOfItems *, delem);
            else
                status = EC_InvalidVR;
        } else
            status = EC_CorruptedData;
    } else {

        sequence = new DcmSequenceOfItems(seqTag);
        if (sequence != NULL)
        {

            status = insert(sequence, OFTrue );
            if (status.bad())
                delete sequence;
        } else
            status = EC_MemoryExhausted;
    }
    if (status.good())
    {
        if (sequence != NULL)
        {
            const unsigned long count = sequence->card();

            if ((count > 0) && (itemNum >= -1) && (itemNum < OFstatic_cast(signed long, count)))
            {
                if (itemNum == -1)
                {

                    item = sequence->getItem(count - 1);
                } else {

                    item = sequence->getItem(OFstatic_cast(unsigned long, itemNum));
                }

            } else {
                unsigned long i = 0;

                const unsigned long itemCount = (itemNum > OFstatic_cast(signed long, count)) ? (itemNum - count + 1) : 1;
                while ((i < itemCount) && status.good())
                {
                    item = new DcmItem();
                    if (item != NULL)
                    {

                        status = sequence->append(item);
                        if (status.bad())
                            delete item;
                    } else
                        status = EC_MemoryExhausted;
                    i++;
                }
            }
        } else
            status = EC_IllegalCall;
    }

    if (status.bad())
        item = NULL;
    else if (item == NULL)
        status = EC_IllegalCall;
    return status;
}
