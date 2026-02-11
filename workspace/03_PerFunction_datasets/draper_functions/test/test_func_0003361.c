getLengthLongestSequence(int firstSeq, int lastSeq)
{
    int _lengthLongestSequence = 0;

    if(firstSeq >= 1 && lastSeq <= numSeqs)
    {
        for(int i = firstSeq; i <= lastSeq; i++)
        {
            if(getSeqLength(i) > _lengthLongestSequence)
            {
                _lengthLongestSequence = getSeqLength(i);
            }
        }
    }
    return _lengthLongestSequence;
}
