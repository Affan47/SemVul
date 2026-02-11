CallWithArguments(ZoneList<Expression*>* args,
                                      CallFunctionFlags flags,
                                      int position) {

  int arg_count = args->length();
  for (int i = 0; i < arg_count; i++) {
    Load(args->at(i));
    frame_->SpillTop();
  }


  CodeForSourcePosition(position);


  InLoopFlag in_loop = loop_nesting() > 0 ? IN_LOOP : NOT_IN_LOOP;
  CallFunctionStub call_function(arg_count, in_loop, flags);
  Result answer = frame_->CallStub(&call_function, arg_count + 1);


  frame_->RestoreContextRegister();
  frame_->SetElementAt(0, &answer);
}
