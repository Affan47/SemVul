_cmsStageAllocPlaceholder(cmsContext ContextID,
                                cmsStageSignature Type,
                                cmsUInt32Number InputChannels,
                                cmsUInt32Number OutputChannels,
                                _cmsStageEvalFn     EvalPtr,
                                _cmsStageDupElemFn  DupElemPtr,
                                _cmsStageFreeElemFn FreePtr,
                                void*             Data)
{
    cmsStage* ph = (cmsStage*) _cmsMallocZero(ContextID, sizeof(cmsStage));

    if (ph == NULL) return NULL;


    ph ->ContextID = ContextID;

    ph ->Type       = Type;
    ph ->Implements = Type;

    ph ->InputChannels  = InputChannels;
    ph ->OutputChannels = OutputChannels;
    ph ->EvalPtr        = EvalPtr;
    ph ->DupElemPtr     = DupElemPtr;
    ph ->FreePtr        = FreePtr;
    ph ->Data           = Data;

    return ph;
}
