RestoreExtendedRollout(move * pm, const char *sz)
{

    evalsetup *pes = &pm->esMove;


    pes->et = EVAL_ROLLOUT;
    RestoreRolloutScore(pm, sz);
    RestoreRolloutTrials(&pes->rc.nGamesDone, sz);
    RestoreRolloutOutput(pm->arEvalMove, sz, "Output");
    RestoreRolloutOutput(pm->arEvalStdDev, sz, "StdDev");
    if (CheckSGFVersion(&sz)) {
        RestoreRolloutInternals(pes, sz);
        RestoreExtendedRolloutContext(&pes->rc, sz);
    }
}
