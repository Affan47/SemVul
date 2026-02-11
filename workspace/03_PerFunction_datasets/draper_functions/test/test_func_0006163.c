compareItems(DcmItem *item1,
                           DcmItem *item2,
                           DcmSequenceOfItems *fromSequence,
                           const unsigned long itemNumber,
                           OFString &reason)
{
    reason.clear();
    OFString tmpString;

    if ((item1 != NULL) && (item2 != NULL))
    {
        const unsigned long card1 = item1->card();
        const unsigned long card2 = item2->card();

        if (card1 == card2)
        {
            unsigned long i = 0;
            OFBool first = OFTrue;
            DcmStack stack1, stack2;

            while (item1->nextObject(stack1, first).good() && item2->nextObject(stack2, first).good())
            {
                if (!compareAttributes(OFstatic_cast(DcmElement *, stack1.top()), OFstatic_cast(DcmElement *, stack2.top()), fromSequence, i++, reason))
                    break;
                first = OFFalse;
            }
        } else {
            reason = "different number of attributes in item: " + constructDifferentNumbersText(card1, card2, tmpString);
            reason += " (" + constructTagNameWithSQ(NULL , fromSequence, itemNumber, tmpString) + ")";
        }
    } else
        reason = "missing item: " + constructTagNameWithSQ(NULL , fromSequence, itemNumber, tmpString);

    return reason.empty();
}
