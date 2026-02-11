writeBody(StringRef FName,
                                                     const FunctionSamples &S) {
  if (std::error_code EC = writeNameIdx(FName))
    return EC;

  encodeULEB128(S.getTotalSamples(), OS);


  encodeULEB128(S.getBodySamples().size(), OS);
  for (const auto &I : S.getBodySamples()) {
    LineLocation Loc = I.first;
    const SampleRecord &Sample = I.second;
    encodeULEB128(Loc.LineOffset, OS);
    encodeULEB128(Loc.Discriminator, OS);
    encodeULEB128(Sample.getSamples(), OS);
    encodeULEB128(Sample.getCallTargets().size(), OS);
    for (const auto &J : Sample.getCallTargets()) {
      StringRef Callee = J.first();
      uint64_t CalleeSamples = J.second;
      if (std::error_code EC = writeNameIdx(Callee))
        return EC;
      encodeULEB128(CalleeSamples, OS);
    }
  }


  encodeULEB128(S.getCallsiteSamples().size(), OS);
  for (const auto &J : S.getCallsiteSamples()) {
    CallsiteLocation Loc = J.first;
    const FunctionSamples &CalleeSamples = J.second;
    encodeULEB128(Loc.LineOffset, OS);
    encodeULEB128(Loc.Discriminator, OS);
    if (std::error_code EC = writeBody(Loc.CalleeName, CalleeSamples))
      return EC;
  }

  return sampleprof_error::success;
}
