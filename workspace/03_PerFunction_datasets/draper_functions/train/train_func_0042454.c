resize()
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omni::internalLock, 1);

  OMNIORB_ASSERT(numObjectsInTable > maxNumObjects ||
		 numObjectsInTable < minNumObjects && objectTableSizeI > 0);

  if (numObjectsInTable > maxNumObjects) {
    ++objectTableSizeI;
  }
  else if (numObjectsInTable < minNumObjects && objectTableSizeI > 0) {
    --objectTableSizeI;
  }
  else
    return;

  int newsizei = objTblSizes[objectTableSizeI];

  if (newsizei == -1) {


    if (omniORB::trace(5)) {
      omniORB::logger l;
      l << "More than " << maxNumObjects << " active objects!  "
	<< "Consider extending the available object table sizes in "
	<< __FILE__ << ".\n";
    }
    objectTableSizeI--;
    maxNumObjects = 1ul << 31;
    return;
  }
  CORBA::ULong newsize = newsizei;

  if (omniORB::trace(15)) {
    omniORB::logger l;
    l << "Object table resizing from " << objectTableSize
      << " to " << newsize << "\n";
  }


  omniObjTableEntry** newtable = new omniObjTableEntry* [newsize];
  CORBA::ULong i;
  for( i = 0; i < newsize; i++ )  newtable[i] = 0;


  for( i = 0; i < objectTableSize; i++ ) {
    omniObjTableEntry* id = objectTable[i];

    while( id ) {
      omniObjTableEntry* next = id->nextInObjectTable();

      _CORBA_ULong j = omni::hash(id->key(), id->keysize()) % newsize;
      *(id->addrOfNextInObjectTable()) = newtable[j];
      newtable[j] = id;

      id = next;
    }
  }


  delete[] objectTable;
  objectTable = newtable;
  objectTableSize = newsize;
  maxNumObjects = objectTableSize * 2 / 3;
  minNumObjects =
    objectTableSizeI ? (objTblSizes[objectTableSizeI - 1] / 3) : 0;
}
