R_DrawShadowMapWorld (qboolean forEnt, vec3_t origin)
{
	int i;

	if (!r_drawworld->value)
		return;

	if ( r_newrefdef.rdflags & RDF_NOWORLDMODEL )
		return;

	if(forEnt)
	{
		vec3_t absmins, absmaxs;

		glUseProgramObjectARB( g_shadowprogramObj );

		glUniform1iARB( g_location_entShadow, 6);
		qglActiveTextureARB(GL_TEXTURE6);
		qglBindTexture(GL_TEXTURE_2D, r_depthtexture2->texnum);

		glUniform1fARB( g_location_xOffset, 1.0/(r_newrefdef.width*r_shadowmapscale->value));
		glUniform1fARB( g_location_yOffset, 1.0/(r_newrefdef.height*r_shadowmapscale->value));

		glUniform1fARB( g_location_fadeShadow, fadeShadow );

		R_InitVArrays(VERT_NO_TEXTURE);

		VectorAdd (currentmodel->mins, origin, absmins);
		VectorAdd (currentmodel->maxs, origin, absmaxs);

		SM_RecursiveWorldNode2 (r_worldmodel->nodes, 15, origin, absmins, absmaxs);

		R_KillVArrays();

		glUseProgramObjectARB( 0 );

		qglActiveTextureARB(GL_TEXTURE0);

		return;
	}
	else
	{
		R_InitVArrays(VERT_NO_TEXTURE);

		SM_RecursiveWorldNode (r_worldmodel->nodes, 15);

		R_KillVArrays();


		for (i=0 ; i<r_newrefdef.num_entities ; i++)
		{
			currententity = &r_newrefdef.entities[i];
			if (currententity->flags & RF_TRANSLUCENT)
				continue;

			currentmodel = currententity->model;

			if (!currentmodel)
			{
				continue;
			}
			if( currentmodel->type == mod_brush)
				BSP_DrawTexturelessBrushModel (currententity);
			else
				continue;
		}
	}
}
