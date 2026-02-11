CreateCode(const CodeDesc& desc,
                              Code::Flags flags,
                              Handle<Object> self_reference,
                              bool immovable) {


  Object* reloc_info;
  { MaybeObject* maybe_reloc_info = AllocateByteArray(desc.reloc_size, TENURED);
    if (!maybe_reloc_info->ToObject(&reloc_info)) return maybe_reloc_info;
  }


  int body_size = RoundUp(desc.instr_size, kObjectAlignment);
  int obj_size = Code::SizeFor(body_size);
  ASSERT(IsAligned(static_cast<intptr_t>(obj_size), kCodeAlignment));
  MaybeObject* maybe_result;


  if (obj_size > MaxObjectSizeInPagedSpace() || immovable) {
    maybe_result = lo_space_->AllocateRawCode(obj_size);
  } else {
    maybe_result = code_space_->AllocateRaw(obj_size);
  }

  Object* result;
  if (!maybe_result->ToObject(&result)) return maybe_result;


  HeapObject::cast(result)->set_map(code_map());
  Code* code = Code::cast(result);
  ASSERT(!isolate_->code_range()->exists() ||
      isolate_->code_range()->contains(code->address()));
  code->set_instruction_size(desc.instr_size);
  code->set_relocation_info(ByteArray::cast(reloc_info));
  code->set_flags(flags);
  if (code->is_call_stub() || code->is_keyed_call_stub()) {
    code->set_check_type(RECEIVER_MAP_CHECK);
  }
  code->set_deoptimization_data(empty_fixed_array());
  code->set_next_code_flushing_candidate(undefined_value());


  if (!self_reference.is_null()) {
    *(self_reference.location()) = code;
  }


  code->CopyFrom(desc);

#ifdef DEBUG
  code->Verify();
#endif
  return code;
}
