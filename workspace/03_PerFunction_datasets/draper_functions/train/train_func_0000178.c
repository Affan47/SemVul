operator=(const Theorem& th) {

    if(this == &th) return *this;
    if(d_thm == th.d_thm) return *this;

    long tmp = th.d_thm;


    if (tmp & 0x1) {
      TheoremValue* tv = (TheoremValue*) (tmp & (~(0x1)));
      DebugAssert(tv->d_refcount > 0,
                  "Theorem::operator=: invariant violated");
      ++(tv->d_refcount);
    }
    else if (tmp != 0) {
      th.exprValue()->incRefcount();
    }


    if (d_thm & 0x1) {
      TheoremValue* tv = thm();
      DebugAssert(tv->d_refcount > 0,
                  "Theorem::operator=: invariant violated");
      if(--(tv->d_refcount) == 0) {
        MemoryManager* mm = tv->getMM();
        delete tv;
        mm->deleteData(tv);
      }
    }
    else if (d_thm != 0) {
      exprValue()->decRefcount();
    }

    d_thm = tmp;

    return *this;
  }
