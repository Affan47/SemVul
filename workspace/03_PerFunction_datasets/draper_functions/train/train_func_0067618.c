selectDumpableObject(DumpableObject *dobj)
{


	if (dobj->namespace)
		dobj->dump = dobj->namespace->dobj.dump;
	else
		dobj->dump = true;
}
