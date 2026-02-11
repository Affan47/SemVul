ddClearLocal(
  DdNode * f)
{
    if (cuddIsConstant(f) || !Cudd_IsComplement(cuddT(f))) {
	return;
    }

    cuddT(f) = Cudd_Regular(cuddT(f));
    ddClearLocal(cuddT(f));
    ddClearLocal(Cudd_Regular(cuddE(f)));
    return;

}
