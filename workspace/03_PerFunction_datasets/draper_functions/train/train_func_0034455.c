Print(ostream& o) const
{
    o << "    " << ASM_CMD_TO_STR[command] << SIZE_TO_STR[size] << '\t';
    if (size == SIZE_NONE)
        oper->PrintBase(o);
    else
        oper->Print(o);
}
