add_PredefOp (pIIR_PosInfo pos, pIIR_Type ret,
		   pIIR_TextLiteral sym, pIIR_Type left,
		   pIIR_Type right)
{
  pIIR_InterfaceList interf =
    mIIR_InterfaceList (pos,
			mIIR_ConstantInterfaceDeclaration (pos, NULL,
							   left, NULL,
							   IR_IN_MODE,
							   false),
			NULL);
  if (right)
    interf->rest =
      mIIR_InterfaceList (pos,
			  mIIR_ConstantInterfaceDeclaration (pos, NULL,
							     right, NULL,
							     IR_IN_MODE,
							     false),
			  NULL);

  add_decl (mIIR_PredefinedFunctionDeclaration (pos, sym, interf, true, ret));
}
