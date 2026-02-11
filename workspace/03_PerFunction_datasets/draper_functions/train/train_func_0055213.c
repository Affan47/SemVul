sq_delete_dups()


{
    struct ks *SQDesc,*SQDesc1,*SQNext;
    int Info;

    for (SQDesc = SelectQHead; SQDesc; SQDesc = SQNext) {
        SQNext = SQDesc->ksSucc;
        Info = SQDesc->ksPointer->oInfo;
        for (SQDesc1 = SQDesc->ksSucc; SQDesc1; SQDesc1 = SQDesc1->ksSucc)
            if (SQDesc->ksPointer == SQDesc1->ksPointer) {
                SQDelete(SQDesc->ksPointer);

                SQDesc1->ksPointer->oInfo = Info;
                break;
            }
    }
}
