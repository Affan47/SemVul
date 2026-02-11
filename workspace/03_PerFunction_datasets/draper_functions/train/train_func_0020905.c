pkix_ForwardBuilderState_IsIOPending(
        PKIX_ForwardBuilderState *state,
        PKIX_Boolean *pPending,
        void *plContext)
{
        PKIX_ENTER(FORWARDBUILDERSTATE, "pkix_ForwardBuilderState_IsIOPending");
        PKIX_NULLCHECK_TWO(state, pPending);

        if ((state->status == BUILD_GATHERPENDING) ||
            (state->status == BUILD_CHECKTRUSTED2) ||
            (state->status == BUILD_VALCHAIN2) ||
            (state->status == BUILD_AIAPENDING)) {
                *pPending = PKIX_TRUE;
        } else {
                *pPending = PKIX_FALSE;
        }

        PKIX_RETURN(FORWARDBUILDERSTATE);
}
