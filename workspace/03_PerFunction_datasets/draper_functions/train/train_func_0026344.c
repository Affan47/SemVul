HandleStepRequest(const std::vector<string>& argv, std::string* out) {
  if(argv[0] == "Address" && argv.size() >= 2) {
    Address* stop;
    Address* a = memory_.ResolveToAddress(0, argv[1]);
    if(argv.size() == 3) {
      stop = memory_.ResolveToAddress(0, argv[2]);
      while (a != stop) {
        if(a->get_instruction() == NULL) instruction_factory_->Process(a);
        Changelist* c = changelist_factory_.CreateFromStatelessChangelist(a, *a->get_instruction()->change_, &memory_);
        memory_.Commit(c);
        a = memory_.ResolveToAddress(0, argv[1]);
      }
    } else {
      if (a != 0) {
        if(a->get_instruction() == NULL) {
          instruction_factory_->Process(a);
          LOG(INFO) << "Disassembled";
        }
        StatelessChangelist* slcl = a->get_instruction()->change_;
        DebugPrint(slcl);
        LOG(DEBUG) << "got address, creating changelist";
        Changelist* c = changelist_factory_.CreateFromStatelessChangelist(a, *slcl, &memory_);
        LOG(DEBUG) << "changelist created";
        memory_.Commit(c);


        JSON ret;
        c->SerializeToJSON(&ret);
        (*out) = ret.serialize();
      }
    }
  }
  return true;
}
