EvalBearoff2(const TanBoard anBoard, float arOutput[], const bgvariation UNUSED(bgv), NNState * UNUSED(nnStates))
{
    g_assert(pbc2);

    return BearoffEval(pbc2, anBoard, arOutput);
}
