getNodeLabel(const MachineBasicBlock *Node,
                             const MachineFunction *Graph) {
      std::string OutStr;
      {
        raw_string_ostream OSS(OutStr);

        if (isSimple()) {
          OSS << "BB#" << Node->getNumber();
          if (const BasicBlock *BB = Node->getBasicBlock())
            OSS << ": " << BB->getName();
        } else
          Node->print(OSS);
      }

      if (OutStr[0] == '\n') OutStr.erase(OutStr.begin());


      for (unsigned i = 0; i != OutStr.length(); ++i)
        if (OutStr[i] == '\n') {
          OutStr[i] = '\\';
          OutStr.insert(OutStr.begin()+i+1, 'l');
        }
      return OutStr;
    }
