get(unsigned Line, unsigned Col, const MDNode *Scope,
                       const MDNode *InlinedAt) {

  if (!Scope)
    return DebugLoc();

  return DILocation::get(Scope->getContext(), Line, Col,
                         const_cast<MDNode *>(Scope),
                         const_cast<MDNode *>(InlinedAt));
}
