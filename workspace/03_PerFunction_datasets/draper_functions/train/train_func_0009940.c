validate_number(const int num,
                                   const char * const desc,
                                   const unsigned int lineno)
  {
    stringstream error_msg;

    if (-1 == num)
      {
        error_msg << desc   << " must be already read before line #"
                  << lineno << ".";
        obErrorLog.ThrowError("FCHKFormat::ReadMolecule()",
                              error_msg.str(),
                              obError);
        return false;
      }
    return true;
  }
