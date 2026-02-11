TryToConvertType(SyntaxNode*& first, SyntaxNode*& second)
{
    if (first->GetSymType() == second->GetSymType()) return;
    SyntaxNode* tmp = ConvertType(first, second->GetSymType());
    if (tmp != NULL)
    {
        first = tmp;
        return;
    }
    tmp = ConvertType(second, first->GetSymType());
    if (tmp != NULL) second = tmp;
}
