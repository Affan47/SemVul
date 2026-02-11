reassignSectionAddress(unsigned SectionID,
                                             uint64_t Addr) {


  DEBUG(dbgs() << "Reassigning address for section "
               << SectionID << " (" << Sections[SectionID].Name << "): "
               << format("0x%016" PRIx64, Sections[SectionID].LoadAddress) << " -> "
               << format("0x%016" PRIx64, Addr) << "\n");
  Sections[SectionID].LoadAddress = Addr;
}
