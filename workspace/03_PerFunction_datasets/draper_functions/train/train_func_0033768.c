Clear_CodeRange( PExecution_Context  exec, Int  range )
  {
    if ( range < 1 || range > 3 )
      return TT_Err_Bad_Argument;

    exec->codeRangeTable[range - 1].Base = (Byte*)NULL;
    exec->codeRangeTable[range - 1].Size = 0;

    return TT_Err_Ok;
  }
