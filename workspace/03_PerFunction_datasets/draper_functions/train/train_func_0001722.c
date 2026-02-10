TryGetFunctionPrototype(Register function,
                                             Register result,
                                             Label* miss) {

  testl(function, Immediate(kSmiTagMask));
  j(zero, miss);


  CmpObjectType(function, JS_FUNCTION_TYPE, result);
  j(not_equal, miss);


  NearLabel non_instance;
  testb(FieldOperand(result, Map::kBitFieldOffset),
        Immediate(1 << Map::kHasNonInstancePrototype));
  j(not_zero, &non_instance);


  movq(result,
       FieldOperand(function, JSFunction::kPrototypeOrInitialMapOffset));


  CompareRoot(result, Heap::kTheHoleValueRootIndex);
  j(equal, miss);


  NearLabel done;
  CmpObjectType(result, MAP_TYPE, kScratchRegister);
  j(not_equal, &done);


  movq(result, FieldOperand(result, Map::kPrototypeOffset));
  jmp(&done);


  bind(&non_instance);
  movq(result, FieldOperand(result, Map::kConstructorOffset));


  bind(&done);
}
