printSequencesAddedInfo()
{
    if(userParameters->getDisplayInfo())
    {
        int startSeq = userParameters->getProfile2Empty() ? 1:
                       profile1NumSeqs + 1;
        string dnaFlag = userParameters->getDNAFlag() ? "bp" : "aa";


        for(int i = startSeq; i <= numSeqs; i++)
        {
            cout << "Sequence " << i << ": "
                 << std::left << setw(maxNames) << names.at(i)
                 << std::right << setw(6) << getSequenceLength(i)
                 << " " << dnaFlag << std::endl;
        }
    }
}
