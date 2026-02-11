getSyntaxString(OFString &syntaxStr) const
{
    syntaxStr.clear();
    if (!ValidOptionList.empty())
        syntaxStr += " [options]";
    if (!ValidParamList.empty())
    {
        OFListConstIterator(OFCmdParam *) iter = ValidParamList.begin();
        OFListConstIterator(OFCmdParam *) last = ValidParamList.end();
        while (iter != last)
        {
            if (!(*iter)->ParamName.empty())
            {
                switch ((*iter)->ParamMode)
                {
                    case OFCmdParam::PM_Mandatory:
                        syntaxStr += " ";
                        syntaxStr += (*iter)->ParamName;
                        break;
                    case OFCmdParam::PM_Optional:
                        syntaxStr += " [";
                        syntaxStr += (*iter)->ParamName;
                        syntaxStr += "]";
                        break;
                    case OFCmdParam::PM_MultiMandatory:
                        syntaxStr += " ";
                        syntaxStr += (*iter)->ParamName;
                        syntaxStr += "...";
                        break;
                    case OFCmdParam::PM_MultiOptional:
                        syntaxStr += " [";
                        syntaxStr += (*iter)->ParamName;
                        syntaxStr += "...]";
                        break;
                }
            }
            ++iter;
        }
    }
}
