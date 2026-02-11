CheckVariableName(int index, const yy::location& loc, bool param)
{
    if (mAllowOverlap && !param) return;

    const ASTrepContainer* thisLevel = param ? &mParamDecls : mContainerStack.back();

    for (ASTparameters::const_reverse_iterator pit = thisLevel->mParameters.rbegin(),
         epit = thisLevel->mParameters.rend(); pit != epit; ++pit)
    {
        if (pit->mName == index) {
            warning(loc, "Scope of name overlaps variable/parameter with same name");
            warning(pit->mLocation, "previous variable/parameter declared here");
        }
    }
}
