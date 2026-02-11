SQComputeBB()


{
    struct ks *SQDesc;
    struct ka BB;
    int Info;

    SelectQBB.kaLeft   = CDINFINITY;
    SelectQBB.kaBottom = CDINFINITY;
    SelectQBB.kaRight  = -CDINFINITY;
    SelectQBB.kaTop    = -CDINFINITY;

    for (SQDesc = SelectQHead; SQDesc != NULL; SQDesc = SQDesc->ksSucc) {
        Info = SQDesc->ksPointer->oInfo;
        if (Info == SQ_OLDSEL || Info == SQ_NEWSEL ||
            (Info > 10 && Info <= 255)) {
            GetBB(SQDesc->ksPointer,&BB);
            UpdateBB(SelectQBB,BB);
        }
    }
}
