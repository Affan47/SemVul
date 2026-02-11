nb_freeWorld(nb_world_t *world) {
	for (int i = 0; i < world->nBodies; i++) {
		sm_freeModel(world->bodies[i].unitSphere);
		free(world->bodies[i].pva);
		free(world->bodies[i].sampleVertices);
		free(world->bodies[i].perceivedForceAtSample);
		free(world->bodies[i].pfNormalComponent);
		free(world->bodies[i].displayVertices);
		free(world->bodies[i].displayNormals);
	}
	free(world->bodies);
	free(world);
}
