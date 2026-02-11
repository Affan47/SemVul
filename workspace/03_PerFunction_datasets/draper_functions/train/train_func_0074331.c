readSequence(DcmItem &dataset,
                                             const DcmTagKey &tagKey,
                                             const OFString &type)
{

    DcmSequenceOfItems dseq(tagKey);
    OFCondition result = DSRTypes::getElementFromDataset(dataset, dseq);
    DSRTypes::checkElementValue(dseq, "1", type, result, "content item");
    if (result.good())
    {
        DcmItem *ditem = dseq.getItem(0);
        if (ditem != NULL)
        {

            result = readItem(*ditem, DcmTag(tagKey).getTagName());
        } else
            result = SR_EC_InvalidDocumentTree;
    }
    return result;
}
