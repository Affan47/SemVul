acdDelPhyloFreq(void** PPval)
{
    ajUser("acdDelPhyloFreq '%x'", *PPval);

    if(!*PPval)
        return;

    ajPhyloFreqDel((AjPPhyloFreq*)PPval);

    return;
}
