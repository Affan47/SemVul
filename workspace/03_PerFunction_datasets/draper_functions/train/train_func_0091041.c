UpdateAllocationTopHelper(Register result_end,
                                               Register scratch) {
  if (emit_debug_code()) {
    testq(result_end, Immediate(kObjectAlignmentMask));
    Check(zero, "Unaligned allocation in new space");
  }

  ExternalReference new_space_allocation_top =
      ExternalReference::new_space_allocation_top_address(isolate());


  if (scratch.is_valid()) {

    movq(Operand(scratch, 0), result_end);
  } else {
    Store(new_space_allocation_top, result_end);
  }
}
