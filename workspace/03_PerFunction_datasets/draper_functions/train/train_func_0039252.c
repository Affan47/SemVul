specPhotTableHeader(VimosTable *table, VimosDescriptor *descs)
{

  char modName[]  = "specPhotTableHeader";
  int  quadrant;


  if (table == NULL) {
    cpl_msg_error(modName, "Null input table");
    return VM_FALSE;
  }

  if (descs == NULL) {
    cpl_msg_error(modName, "Null input descriptors");
    return VM_FALSE;
  }

  if (strcmp(table->name, VM_SPHOT)) {
    cpl_msg_error(modName, "Invalid input table");
    return (VM_FALSE);
  }

  if (readIntDescriptor(descs, pilTrnGetKeyword("Quadrant"),
                        &quadrant, NULL) != VM_TRUE)
    return 0;

  if (vimosDscCopy(&(table->descs), descs, ".*-OBS$", 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, pilTrnGetKeyword("Instrument"), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, "^ESO OBS (DID|ID|PROG ID)", 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, pilTrnGetKeyword("INS.DID"), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("InstrumentMode"), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("FilterId", quadrant), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("FilterName", quadrant), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, pilTrnGetKeyword("DET.DID"), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("Adu2Electron", 1), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("ReadNoise", 1), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("Electron2Adu", 1), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("GrismId", quadrant), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   pilTrnGetKeyword("GrismName", quadrant), 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs,
                   "^ESO DET READ (CLOCK|SPEED|MODE)", 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, "^ESO OCS (CON QUAD|DID)", 0))
      return 0;

  if (vimosDscCopy(&(table->descs), descs, pilTrnGetKeyword("Airmass"), 0))
      return 0;

  return VM_TRUE;

}
