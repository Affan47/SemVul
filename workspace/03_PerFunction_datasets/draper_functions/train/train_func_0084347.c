RGD_AddNewRagdoll( vec3_t origin, char name[MAX_QPATH] )
{
	int RagDollID, i;
	vec3_t dist;
	vec3_t dir;


	for(RagDollID = 0; RagDollID < MAX_RAGDOLLS; RagDollID++)
	{
		if(!RagDoll[RagDollID].destroyed)
		{
			VectorSubtract(origin, RagDoll[RagDollID].origin, dist);
			if(VectorLength(dist) < 64 && !strcmp(RagDoll[RagDollID].name, name))
				return;
		}
	}

	VectorSet(dir, 6, 6, 20);

	r_DrawingRagDoll = true;


	for(RagDollID = 0; RagDollID < MAX_RAGDOLLS; RagDollID++)
	{
		if(RagDoll[RagDollID].destroyed)
		{
			RGD_RagdollBody_Init(RagDollID, origin, name);

			if(r_ragdoll_debug->integer == 2)
			{
				Com_Printf("RagDoll name: %s Ent name: %s Mesh: %s Ent Mesh: %s\n", RagDoll[RagDollID].name, name,
					RagDoll[RagDollID].ragDollMesh->name, currentmodel->name);

				for(i = 0; i < 27; i++)
					Com_Printf("ragdoll val %i: %4.2f\n", i, RagDoll[RagDollID].ragDollMesh->ragdoll.RagDollDims[i]);
			}

			if(r_ragdoll_debug->integer)
				Com_Printf("Added a ragdoll @ %4.2f,%4.2f,%4.2f\n", RagDoll[RagDollID].origin[0], RagDoll[RagDollID].origin[1],
					RagDoll[RagDollID].origin[2]);


			if(RagDoll[RagDollID].ragDollMesh->ragdoll.hasHelmet)
				CL_GlassShards(RagDoll[RagDollID].origin, dir, 5);
			break;
		}
	}
}
