removeInvalidGroups(const OFBool cmdSet)
{
    DcmStack stack;
    DcmObject *object = NULL;

    if (cmdSet)
    {

        while (nextObject(stack, OFTrue).good())
        {
            object = stack.top();

            if (object->getGTag() != 0x0000)
            {
                DCMDATA_DEBUG("DcmDataset::removeInvalidGroups() removing element "
                    << object->getTag() << " from command set");
                stack.pop();

                delete OFstatic_cast(DcmItem *, stack.top())->remove(object);
            }
        }
    } else {

        while (nextObject(stack, OFTrue).good())
        {
            object = stack.top();

            if ((object->getGTag() == 0x0000) || (object->getGTag() == 0x0002) ||
                !object->getTag().hasValidGroup())
            {
                DCMDATA_DEBUG("DcmDataset::removeInvalidGroups() removing element "
                    << object->getTag() << " from data set");
                stack.pop();

                delete OFstatic_cast(DcmItem *, stack.top())->remove(object);
            }

            else if ((stack.card() > 2) && (object->getGTag() == 0x0006))
            {
                DCMDATA_DEBUG("DcmDataset::removeInvalidGroups() removing element "
                    << object->getTag() << " from sequence item");
                stack.pop();

                delete OFstatic_cast(DcmItem *, stack.top())->remove(object);
            }
        }
    }
}
