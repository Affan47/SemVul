outputSolverTargetFields_sif(ostream& out, short indent_size, short indent_level, const char* source_eq_name, NameSet& targetFieldNames)
{
  UserInterface* gui = (UserInterface*)model->getGui();


  for (short i = 0; i < nofFields; i++) {

    ParameterField* pf = fields[i];


    if ( !pf->isActiveInstance() ||
         pf->getNofDataStrings() == 0 ||
         !pf->isSifOutputField()
       )
      continue;

    if ( !gui->getIsSolverTargetField(source_eq_name, pf->getGuiName()) ) {
      continue;
    }

    std::pair<NameSet::iterator, bool> tfPair;


    tfPair = targetFieldNames.insert(pf->getGuiName());


    if ( !tfPair.second ) continue;


    pf->output_sif(out, indent_size, indent_level, SIF_SOLVER);

  }

  return out;

}
