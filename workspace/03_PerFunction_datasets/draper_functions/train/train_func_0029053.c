lp_declare_intrinsic(LLVMModuleRef module,
                     const char *name,
                     LLVMTypeRef ret_type,
                     LLVMTypeRef *arg_types,
                     unsigned num_args)
{
   LLVMTypeRef function_type;
   LLVMValueRef function;

   assert(!LLVMGetNamedFunction(module, name));

   function_type = LLVMFunctionType(ret_type, arg_types, num_args, 0);
   function = LLVMAddFunction(module, name, function_type);

   LLVMSetFunctionCallConv(function, LLVMCCallConv);
   LLVMSetLinkage(function, LLVMExternalLinkage);

   assert(LLVMIsDeclaration(function));

   return function;
}
