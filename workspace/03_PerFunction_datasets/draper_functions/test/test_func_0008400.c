cfunction_invoke(struct cfunction* function, jv input[]) {
  switch (function->nargs) {
  case 1: return ((func_1)function->fptr)(input[0]);
  case 2: return ((func_2)function->fptr)(input[0], input[1]);
  case 3: return ((func_3)function->fptr)(input[0], input[1], input[2]);
  case 4: return ((func_4)function->fptr)(input[0], input[1], input[2], input[3]);
  case 5: return ((func_5)function->fptr)(input[0], input[1], input[2], input[3], input[4]);
  default: return jv_invalid_with_msg(jv_string("Function takes too many arguments"));
  }
}
