GetExtentTranslator(vtkInformation *info)
{
  if(!info)
    {
    vtkErrorMacro("Attempt to get translator for invalid output");
    return 0;
    }
  vtkExtentTranslator* translator =
    vtkExtentTranslator::SafeDownCast(info->Get(EXTENT_TRANSLATOR()));
  if(!translator)
    {
    translator = vtkExtentTranslator::New();
    info->Set(EXTENT_TRANSLATOR(), translator);
    translator->Delete();
    }
  return translator;
}
