AllocateInNewSpace(Register object_size,
                                        Register result,
                                        Register result_end,
                                        Register scratch,
                                        Label* gc_required,
                                        AllocationFlags flags) {
  if (!FLAG_inline_new) {
    if (FLAG_debug_code) {

      movl(result, Immediate(0x7091));
      movl(result_end, Immediate(0x7191));
      if (scratch.is_valid()) {
        movl(scratch, Immediate(0x7291));
      }

    }
    jmp(gc_required);
    return;
  }
  ASSERT(!result.is(result_end));


  LoadAllocationTopHelper(result, scratch, flags);


  ExternalReference new_space_allocation_limit =
      ExternalReference::new_space_allocation_limit_address();
  if (!object_size.is(result_end)) {
    movq(result_end, object_size);
  }
  addq(result_end, result);
  j(carry, gc_required);
  movq(kScratchRegister, new_space_allocation_limit);
  cmpq(result_end, Operand(kScratchRegister, 0));
  j(above, gc_required);


  UpdateAllocationTopHelper(result_end, scratch);


  if ((flags & TAG_OBJECT) != 0) {
    addq(result, Immediate(kHeapObjectTag));
  }
}
