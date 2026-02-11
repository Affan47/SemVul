scalarErrorCheck(TIntermTyped* node, const char* token)
{
    if (node->isScalar())
        return false;

   error(node->getLine(), "scalar expression required", token, "");

   return true;
}
