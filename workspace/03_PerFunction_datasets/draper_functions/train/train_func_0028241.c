reverseContainers(Aword adr)
{
  ContainerEntry *e = (ContainerEntry *) &memory[adr];

  if (alreadyDone(adr)) return;

  if (!isEndOfArray(e)) {
    reverseTable(adr, sizeof(ContainerEntry));
    while (!isEndOfArray(e)) {
      reverseLims(e->limits);
      reverseStms(e->header);
      reverseStms(e->empty);
      reverseChks(e->extractChecks);
      reverseStms(e->extractStatements);
      e++;
    }
  }
}
