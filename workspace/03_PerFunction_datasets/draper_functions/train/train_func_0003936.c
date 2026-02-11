DumpFunction(TFunc* tf, FILE* D)
{
 ThreadCode(tf->code,tf->code+tf->size);
 fputc(ID_FUN,D);
 DumpSize(tf->size,D);
 DumpWord(tf->lineDefined,D);
 if (IsMain(tf))
  DumpString(tf->fileName,D);
 else
  DumpWord(tf->marked,D);
 DumpBlock(tf->code,tf->size,D);
 DumpStrings(D);
}
