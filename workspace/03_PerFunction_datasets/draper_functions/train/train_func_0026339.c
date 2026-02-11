createTableEntry(const char * const name,
				dimeMemHandler * const memhandler)
{
  if (!strcmp(name, "LAYER")) {
    return new(memhandler) dimeLayerTable;
  }


  return new(memhandler) dimeUnknownTable(name, memhandler);
}
