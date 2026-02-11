DoMoo2(CommandLine &)
{

   if (_config->FindI("quiet") >= 2)
      return printMooLine();
   std::string const moo = getMooLine();
   size_t const depth = moo.length()/4;
   if (_config->FindB("APT::Moo::Color", false) == false)
      c1out <<
	 OutputInDepth(depth, " ") << "         (__)  \n" <<
	 OutputInDepth(depth, " ") << " _______~(..)~ \n" <<
	 OutputInDepth(depth, " ") << "   ,----\\(oo) \n" <<
	 OutputInDepth(depth, " ") << "  /|____|,'    \n" <<
	 OutputInDepth(depth, " ") << " * /\"\\ /\\   \n" <<
	 OutputInDepth(depth, " ") << "   ~ ~ ~ ~     \n" <<
	 moo;
   else
   {
      c1out <<
	 OutputInDepth(depth, " ") << "         \033[1;97m(\033[0;33m__\033[1;97m)\033[0m\n" <<
	 OutputInDepth(depth, " ") << " \033[31m_______\033[33m~(\033[1;34m..\033[0;33m)~\033[0m\n" <<
	 OutputInDepth(depth, " ") << "   \033[33m,----\033[31m\\\033[33m(\033[1;4;35moo\033[0;33m)\033[0m\n" <<
	 OutputInDepth(depth, " ") << "  \033[33m/|____|,'\033[0m\n" <<
	 OutputInDepth(depth, " ") << " \033[1;5;97m*\033[0;33m /\\  /\\\033[0m\n" <<
	 "\033[32m";
      for (size_t i = moo.length()/2; i > 1; --i)
	 c1out << "wW";

      c1out << "w\033[0m\n" << moo;
   }

   return true;
}
