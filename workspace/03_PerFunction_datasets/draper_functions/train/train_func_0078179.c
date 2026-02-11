AppendTarget(cmGeneratedFileStream& fout,
                                               const std::string&     target,
                                               const std::string&     make)
{
  fout <<
    "<target name=\"" << target << "\""
    " path=\"\""
    " targetID=\"org.eclipse.cdt.make.MakeTargetBuilder\">\n"
    "<buildCommand>"
    << cmExtraEclipseCDT4Generator::GetEclipsePath(make)
    << "</buildCommand>\n"
    "<buildArguments/>\n"
    "<buildTarget>" << target << "</buildTarget>\n"
    "<stopOnError>true</stopOnError>\n"
    "<useDefaultCommand>false</useDefaultCommand>\n"
    "</target>\n"
    ;
}
