PrintPrototype(ostream& o, int offset) const
{
    o << token.GetName();
    if (params.size() > 0)
    {
        o << "(";
        params.front()->Print(o, 0);
        for (vector<SymVarParam*>::const_iterator it = ++params.begin(); it != params.end(); ++it)
        {
            o << "; ";
            if ((*it)->IsByRef()) o << "var ";
            (*it)->Print(o, 0);
        }
        o << ")";
    }
}
