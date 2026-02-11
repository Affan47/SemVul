getHashTableEntry (unsigned long hashedValue)
{
    hashEntry **const table = getHashTable ();
    hashEntry *entry;

    Assert (hashedValue < TableSize);
    entry = table [hashedValue];

    return entry;
}
