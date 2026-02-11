ComplainAboutMissingTarget(cmTarget* depender,
                             cmTarget* dependee,
                             int occurrences)
{
  cmOStringStream e;
  e << "install(EXPORT \""
    << this->IEGen->GetExportSet()->GetName()
    << "\" ...) "
    << "includes target \"" << depender->GetName()
    << "\" which requires target \"" << dependee->GetName() << "\" ";
  if (occurrences == 0)
    {
    e << "that is not in the export set.";
    }
  else
    {
    e << "that is not in this export set, but " << occurrences
    << " times in others.";
    }
  cmSystemTools::Error(e.str().c_str());
}
