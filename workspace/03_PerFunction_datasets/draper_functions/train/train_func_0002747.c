radeon_llvm_get_kernel_module(LLVMContextRef ctx, unsigned index,
		const unsigned char *bitcode, unsigned bitcode_len)
{
	LLVMModuleRef mod;
	unsigned num_kernels;
	LLVMValueRef *kernel_metadata;
	unsigned i;

	mod = radeon_llvm_parse_bitcode(ctx, bitcode, bitcode_len);
	num_kernels = LLVMGetNamedMetadataNumOperands(mod, "opencl.kernels");
	kernel_metadata = MALLOC(num_kernels * sizeof(LLVMValueRef));
	LLVMGetNamedMetadataOperands(mod, "opencl.kernels", kernel_metadata);
	for (i = 0; i < num_kernels; i++) {
		LLVMValueRef kernel_signature, kernel_function;
		if (i == index) {
			continue;
		}
		kernel_signature = kernel_metadata[i];
		LLVMGetMDNodeOperands(kernel_signature, &kernel_function);
		LLVMDeleteFunction(kernel_function);
	}
	FREE(kernel_metadata);
	radeon_llvm_optimize(mod);
	return mod;
}
