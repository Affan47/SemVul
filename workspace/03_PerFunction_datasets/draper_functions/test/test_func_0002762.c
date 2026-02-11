_dxfGetViewMatrix(void *stack, float m[4][4])
{

  register tdmTransformStackP tdmStack = (tdmTransformStackP) stack ;

  ENTRY(("_dxfGetViewMatrix(0x%x, 0x%x)", stack, m));

  COPYMATRIX(m, tdmStack->vTop->m) ;

  EXIT((""));
}
