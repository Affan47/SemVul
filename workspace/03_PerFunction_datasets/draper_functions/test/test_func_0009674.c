read(DcmItem &dataset)
{

    getAndCheckStringValueFromDataset(dataset, DCM_RetrieveAETitle, RetrieveAETitle, "1-n", "3", "ReferencedSeriesSequence");
    getAndCheckStringValueFromDataset(dataset, DCM_StorageMediaFileSetID, StorageMediaFileSetID, "1", "3", "ReferencedSeriesSequence");
    getAndCheckStringValueFromDataset(dataset, DCM_StorageMediaFileSetUID, StorageMediaFileSetUID, "1", "3", "ReferencedSeriesSequence");

    DcmSequenceOfItems sequence(DCM_ReferencedSOPSequence);
    OFCondition result = getElementFromDataset(dataset, sequence);
    checkElementValue(sequence, "1-n", "1", result);
    if (result.good())
    {

        for (unsigned long i = 0; i < sequence.card(); i++)
        {
            DcmItem *item = sequence.getItem(i);
            if (item != NULL)
            {

                OFString sopClassUID, instanceUID;
                if (getAndCheckStringValueFromDataset(*item, DCM_ReferencedSOPClassUID, sopClassUID, "1", "1", "ReferencedSOPSequence").good() &&
                    getAndCheckStringValueFromDataset(*item, DCM_ReferencedSOPInstanceUID, instanceUID, "1", "1", "ReferencedSOPSequence").good())
                {

                    InstanceStruct *instance = gotoInstance(instanceUID);
                    if (instance == NULL)
                    {

                        instance = new InstanceStruct(sopClassUID, instanceUID);
                        if (instance != NULL)
                        {

                            InstanceList.push_back(instance);

                            Iterator = --InstanceList.end();
                        } else {
                            result = EC_MemoryExhausted;
                            break;
                        }
                    } else {

                        DCMSR_WARN("SOP Instance \"" << instanceUID << "\" already exists in reference list ... ignoring");
                    }
                }
            }
        }
    }
    return result;
}
