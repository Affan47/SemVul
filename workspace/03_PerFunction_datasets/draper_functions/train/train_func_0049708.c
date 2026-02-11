R_DestroyRagDoll(int RagDollID, qboolean nuke)
{
	int i;

	VectorSet(RagDoll[RagDollID].origin, 0, 0, 0);


	for( i = 0; i < MAX_FORCES; i++)
	{
		RagDoll[RagDollID].RagDollForces[i].destroyed = true;
	}


	if(RagDoll[RagDollID].ragDollMesh)
	{
		free(RagDoll[RagDollID].ragDollMesh);
		RagDoll[RagDollID].ragDollMesh = NULL;
	}

    if(RagDoll[RagDollID].initframe)
	{
        free(RagDoll[RagDollID].initframe);
		RagDoll[RagDollID].initframe = NULL;
	}

	if(RagDoll[RagDollID].script)
	{
		if(RagDoll[RagDollID].script->stage)
		{
			if(RagDoll[RagDollID].script->stage->next)
			{
				free(RagDoll[RagDollID].script->stage->next);
				RagDoll[RagDollID].script->stage->next = NULL;
			}
			free(RagDoll[RagDollID].script->stage);
			RagDoll[RagDollID].script->stage = NULL;
		}

		free(RagDoll[RagDollID].script);
		RagDoll[RagDollID].script = NULL;
	}

	if(!nuke)
		return;


	for(i = CHEST; i <= LEFTHAND; i++)
	{
		if(RagDoll[RagDollID].RagDollObject[i].geom)
			dGeomDestroy(RagDoll[RagDollID].RagDollObject[i].geom);
		RagDoll[RagDollID].RagDollObject[i].geom = NULL;
		if(RagDoll[RagDollID].RagDollObject[i].body)
			dBodyDestroy(RagDoll[RagDollID].RagDollObject[i].body);
		RagDoll[RagDollID].RagDollObject[i].body = NULL;
	}

	for(i = MIDSPINE; i <= LEFTWRIST; i++)
	{
		if(RagDoll[RagDollID].RagDollJoint[i])
			dJointDestroy(RagDoll[RagDollID].RagDollJoint[i]);
		RagDoll[RagDollID].RagDollJoint[i] = NULL;
	}
}
