globalErrorCheck(const TSourceLoc& line, bool global, const char* token)
{
   if (global)
      return false;

   error(line, "only allowed at global scope", token, "");

   return true;
}
