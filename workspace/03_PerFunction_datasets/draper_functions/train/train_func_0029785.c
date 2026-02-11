WriteHandler(X6502 *X, unsigned int A, uint8 V)
{
 extern X6502 XSave;

 if(X->preexec)
  FindBPoint(&XSave,BPOINT_WRITE,A);
 else
  BWrite[A](A,V);
}
