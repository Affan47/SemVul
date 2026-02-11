addArgumentsAPTCDROM(std::vector<CommandLine::Args> &Args, char const * const Cmd)
{
   if (CmdMatches("add", "ident") == false)
      return false;


   addArg(0, "auto-detect", "Acquire::cdrom::AutoDetect", CommandLine::Boolean);
   addArg('d', "cdrom", "Acquire::cdrom::mount", CommandLine::HasArg);
   addArg('r', "rename", "APT::CDROM::Rename", 0);
   addArg('m', "no-mount", "APT::CDROM::NoMount", 0);
   addArg('f', "fast", "APT::CDROM::Fast", 0);
   addArg('n', "just-print", "APT::CDROM::NoAct", 0);
   addArg('n', "recon", "APT::CDROM::NoAct", 0);
   addArg('n', "no-act", "APT::CDROM::NoAct", 0);
   addArg('a', "thorough", "APT::CDROM::Thorough", 0);
   return true;
}
