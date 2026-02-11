TraverseBlock4ScalarExpansion(Block *bHead)
{
    Block *b;

    for (b = bHead; b != NULL; b = b->next) {
	if (IsTargetLoop(b))
	    DoScalarExpansion(b);
	else
	    TraverseBlock4ScalarExpansion(b->inner);
    }
}
