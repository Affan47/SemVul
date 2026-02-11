PV_ComplementarySequence(char *sequence)
{
    char T_or_U;
    GB_ERROR error  = GBT_determine_T_or_U(ED4_ROOT->alignment_type, &T_or_U, "complement");
    if (error) {
        cout<<error<<endl;
        return PV_FAILED;
    }

    int seqLen = strlen(sequence);
    char *complementarySeq  = GBT_complementNucSequence((const char*) sequence, seqLen, T_or_U);
    strcpy(sequence, complementarySeq);
    return PV_SUCCESS;
}
