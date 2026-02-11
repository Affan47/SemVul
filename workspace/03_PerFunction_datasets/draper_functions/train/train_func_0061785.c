dispose(Space& home) {
    Advisors<Advisor> as(c);
    x.cancel(home,as.advisor());
    c.dispose(home);
    (void) MixNaryOnePropagator<BoolView,PC_BOOL_NONE,IntView,PC_INT_DOM>
      ::dispose(home);
    return sizeof(*this);
  }
