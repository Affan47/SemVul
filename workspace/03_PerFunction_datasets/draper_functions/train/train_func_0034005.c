removeFromLeaderTable(uint32_t N, Value *V, BasicBlock *BB) {
      LeaderTableEntry* Prev = 0;
      LeaderTableEntry* Curr = &LeaderTable[N];

      while (Curr->Val != V || Curr->BB != BB) {
        Prev = Curr;
        Curr = Curr->Next;
      }

      if (Prev) {
        Prev->Next = Curr->Next;
      } else {
        if (!Curr->Next) {
          Curr->Val = 0;
          Curr->BB = 0;
        } else {
          LeaderTableEntry* Next = Curr->Next;
          Curr->Val = Next->Val;
          Curr->BB = Next->BB;
          Curr->Next = Next->Next;
        }
      }
    }
