vc_bvReadMemoryArray(VC vc,
				     Expr array,
				     Expr byteIndex, int numOfBytes) {

  DebugAssert(0 < numOfBytes,
	      "number of Bytes must be greater than 0\n");

  if(numOfBytes == 1)
    return vc_readExpr(vc,array,byteIndex);
  else {
    int count = 1;
    Expr a = vc_readExpr(vc,array,byteIndex);
    while(--numOfBytes > 0) {
      Expr b = vc_readExpr(vc,array,

				       vc_bvPlusExpr(vc, 32,
						     byteIndex,
						     vc_bvConstExprFromInt(vc,32,count)));
      a = vc_bvConcatExpr(vc,b,a);
      count++;
    }
    return a;
  }
}
