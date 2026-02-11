shouldAvoidImmediateInstFormsForSize(SDNode *N) const {
      uint32_t UseCount = 0;


      if (!OptForSize)
        return false;


      for (SDNode::use_iterator UI = N->use_begin(),
           UE = N->use_end(); (UI != UE) && (UseCount < 2); ++UI) {

        SDNode *User = *UI;


        if (User->isMachineOpcode()) {
          UseCount++;
          continue;
        }


        if (User->getOpcode() == ISD::STORE &&
            User->getOperand(1).getNode() == N) {
          UseCount++;
          continue;
        }


        if (User->getNumOperands() != 2)
          continue;


        if (User->getOpcode() == X86ISD::ADD ||
            User->getOpcode() == ISD::ADD    ||
            User->getOpcode() == X86ISD::SUB ||
            User->getOpcode() == ISD::SUB) {


          SDValue OtherOp = User->getOperand(0);
          if (OtherOp.getNode() == N)
            OtherOp = User->getOperand(1);


          RegisterSDNode *RegNode;
          if (OtherOp->getOpcode() == ISD::CopyFromReg &&
              (RegNode = dyn_cast_or_null<RegisterSDNode>(
                 OtherOp->getOperand(1).getNode())))
            if ((RegNode->getReg() == X86::ESP) ||
                (RegNode->getReg() == X86::RSP))
              continue;
        }


        UseCount++;
      }


      return (UseCount > 1);
    }
