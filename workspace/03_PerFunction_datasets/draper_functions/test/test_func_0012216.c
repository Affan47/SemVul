cmDependsFortranParser_RuleUse(cmDependsFortranParser* parser,
                                    const char* name)
{
  if(!parser->InPPFalseBranch)
    {
    parser->Info.Requires.insert(cmSystemTools::LowerCase(name) );
    }
}
