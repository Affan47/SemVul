ReverseComplement(string& sequence) {


    size_t seqLength = sequence.length();
    for ( size_t i = 0; i < seqLength; ++i )
        sequence.replace(i, 1, 1, REVCOMP_LOOKUP[(int)sequence.at(i) - 65]);


    Reverse(sequence);
}
