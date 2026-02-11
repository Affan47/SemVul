findDependencyLoops(DumpableObject **objs, int nObjs, int totObjs)
{


	DumpableObject **workspace;
	int			initiallen;
	bool		fixedloop;
	int			i;

	workspace = (DumpableObject **) malloc(totObjs * sizeof(DumpableObject *));
	if (workspace == NULL)
		exit_horribly(NULL, modulename, "out of memory\n");
	initiallen = 0;
	fixedloop = false;

	for (i = 0; i < nObjs; i++)
	{
		DumpableObject *obj = objs[i];
		int			newlen;

		workspace[initiallen] = NULL;

		if (findLoop(obj, obj->dumpId, workspace, initiallen, &newlen))
		{

			repairDependencyLoop(&workspace[initiallen], newlen - initiallen);

			initiallen = newlen;
			fixedloop = true;
		}
		else
		{


			if (workspace[initiallen] == obj)
				initiallen++;
		}
	}


	if (!fixedloop)
		exit_horribly(NULL, modulename, "could not identify dependency loop\n");

	free(workspace);
}
