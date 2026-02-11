CreateModulesSection()
{
  cmDocumentationSection *sec =
    new cmDocumentationSection("Standard CMake Modules", "MODULES");
  this->AllSections["Modules"] = sec;
  std::string cmakeModules = this->CMakeRoot;
  cmakeModules += "/Modules";
  cmsys::Directory dir;
  dir.Load(cmakeModules.c_str());
  if (dir.GetNumberOfFiles() > 0)
    {
    sec->Append(cmDocumentationModulesHeader[0]);
    sec->Append(cmModulesDocumentationDescription);
    this->CreateModuleDocsForDir(dir, *this->AllSections["Modules"]);
    }
  return true;
}
