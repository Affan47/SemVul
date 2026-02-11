SetDebugBreakAtIC() {


  original_rinfo()->set_target_address(rinfo()->target_address());

  RelocInfo::Mode mode = rmode();
  if (RelocInfo::IsCodeTarget(mode)) {
    Address target = rinfo()->target_address();
    Handle<Code> code(Code::GetCodeFromTargetAddress(target));


    Handle<Code> dbgbrk_code(Debug::FindDebugBreak(code, mode));
    rinfo()->set_target_address(dbgbrk_code->entry());
  }
}
