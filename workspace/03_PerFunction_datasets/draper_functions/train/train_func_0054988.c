DumpHTML(const char* outname)
{
  std::ofstream fout(outname);
  if(!fout)
    {
    std::cerr << "failed to open output file: " << outname << "\n";
    cmSystemTools::ReportLastSystemError("");
    return -1;
    }

  cmake cmi;
  cmDocumentation doc;
  std::vector<cmDocumentationEntry> commands;
  cmi.GetCommandDocumentation(commands);
  cmOStringStream str;
  str << "Documentation for Commands of CMake "
    << cmVersion::GetCMakeVersion();
  doc.SetSection(str.str().c_str(), commands);
  doc.Print(cmDocumentation::HTMLForm, fout);

  return 0;
}
