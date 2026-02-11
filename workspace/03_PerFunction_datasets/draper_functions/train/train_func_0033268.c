PrintVerbose(ostream& o, int offset) const
{
    PrintSpaces(o, offset) << token.GetName() << ": ";
    if (type->GetClassName() & SYM_TYPE_ALIAS)
        type->Print(o, offset + 1);
    else
        type->PrintVerbose(o, offset + 1);
    o << "\n";
}
