commandLineReadSeq(int firstSeq)
{

    alignmentObj.clearAlignment();
    userParameters->setProfileNum(0);
    int code = 0;
    string offendingSeq;
    FileReader readInputFile;
    code = readInputFile.readSeqs(&alignmentObj, firstSeq, &offendingSeq);

    if(code != OK)
    {
        if(code == CANNOTOPENFILE)
        {
            utilityObject->error("Cannot open input file. No alignment!\n");
        }
        else if(code == NOSEQUENCESINFILE)
        {
            utilityObject->error("No sequences in file. No alignment!\n");
        }
        else if(code == ALLNAMESNOTDIFFERENT)
        {
            utilityObject->error("Multiple sequences found with same name (found %s at least twice)!", offendingSeq.c_str());
        }
        else if(code == EMPTYSEQUENCE)
        {
            utilityObject->error("Empty sequences found: %s\n", offendingSeq.c_str());
        }
        else if(code == SEQUENCETOOBIG)
        {
            utilityObject->error("Sequence(s) too big: %s\n", offendingSeq.c_str());
        }
        else if(code == BADFORMAT)
        {
            utilityObject->error("Sequences are badly formatted!\n");
        }
        else
        {
            utilityObject->error("\nThere was a problem reading in the file. No alignment!\n");
        }
        exit(-1);
    }

    alignmentObj.printSequencesAddedInfo();

    userParameters->setEmpty(false);
    return code;
}
