ddSuppInteract(
  DdNode * f,
  char * support)
{
    if (cuddIsConstant(f) || Cudd_IsComplement(cuddT(f))) {
	return;
    }

    support[f->index] = 1;
    ddSuppInteract(cuddT(f),support);
    ddSuppInteract(Cudd_Regular(cuddE(f)),support);

    cuddT(f) = Cudd_Complement(cuddT(f));
    f->next = Cudd_Complement(f->next);
    return;

}
