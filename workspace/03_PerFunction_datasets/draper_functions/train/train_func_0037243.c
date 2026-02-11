OsiSymSolverInterface(const OsiSymSolverInterface & si)
{
   env_= sym_create_copy_environment(si.getSymphonyEnvironment());

   gutsOfConstructor();


   setApplicationData(si.getApplicationData());
}
