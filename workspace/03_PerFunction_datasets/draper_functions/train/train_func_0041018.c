setXComb(tStdXCombPtr xc) {

  MEGroup::setXComb(xc);
  MEVector::const_iterator me = dependent().begin();
  tStdXCombGroupPtr group = dynamic_ptr_cast<tStdXCombGroupPtr>(xc);
  assert(group);
  StdDepXCVector::const_iterator depxc = group->dependent().begin();
  for ( ; me != dependent().end(); ++me, ++depxc ) {
    theKernelMap[*me]->setXComb(*depxc);
  }


  if ( lastCuts().jetFinder() )
    lastCuts().jetFinder()->minOutgoing(lastXComb().mePartonData().size()-1);

  if ( verbose() ) {
    generator()->log()
      << "=== PowhegInclusiveME XComb hierarchies ========================================\n";
    dumpInfo();
    generator()->log()
      << "================================================================================\n";
  }

}
