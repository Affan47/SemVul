printCoverage(raw_ostream &OS,
                             const GCOVCoverage &Coverage) const {
  OS << format("Lines executed:%.2f%% of %u\n",
               double(Coverage.LinesExec) * 100 / Coverage.LogicalLines,
               Coverage.LogicalLines);
  if (Options.BranchInfo) {
    if (Coverage.Branches) {
      OS << format("Branches executed:%.2f%% of %u\n",
                   double(Coverage.BranchesExec) * 100 / Coverage.Branches,
                   Coverage.Branches);
      OS << format("Taken at least once:%.2f%% of %u\n",
                   double(Coverage.BranchesTaken) * 100 / Coverage.Branches,
                   Coverage.Branches);
    } else {
      OS << "No branches\n";
    }
    OS << "No calls\n";
  }
}
