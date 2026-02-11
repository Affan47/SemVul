make(CdlNode node_arg, std::string name_arg, int argc_arg, const char* argv_arg[],
                              std::vector<std::pair<std::string,std::string> >& options_arg)
{
    return new CdlProperty_MinimalBody(node_arg, name_arg, argc_arg, argv_arg, options_arg);
}
