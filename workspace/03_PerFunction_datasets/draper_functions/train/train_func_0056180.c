RecordTickSample(const TickSample& sample) {

  ScopedVector<CodeEntry*> entries(sample.frames_count + 3);


  CodeEntry** entry = entries.start();
  memset(entry, 0, entries.length() * sizeof(*entry));
  if (sample.pc != NULL) {
    *entry++ = code_map_.FindEntry(sample.pc);

    if (sample.has_external_callback) {


      *(entries.start()) = NULL;
      *entry++ = code_map_.FindEntry(sample.external_callback);
    } else if (sample.tos != NULL) {


      *entry = code_map_.FindEntry(sample.tos);
      if (*entry != NULL && !(*entry)->is_js_function()) {
        *entry = NULL;
      }
      entry++;
    }

    for (const Address *stack_pos = sample.stack,
           *stack_end = stack_pos + sample.frames_count;
         stack_pos != stack_end;
         ++stack_pos) {
      *entry++ = code_map_.FindEntry(*stack_pos);
    }
  }

  if (FLAG_prof_browser_mode) {
    bool no_symbolized_entries = true;
    for (CodeEntry** e = entries.start(); e != entry; ++e) {
      if (*e != NULL) {
        no_symbolized_entries = false;
        break;
      }
    }

    if (no_symbolized_entries) {
      *entry++ = EntryForVMState(sample.state);
    }
  }

  profiles_->AddPathToCurrentProfiles(entries);
}
