populatePeerMask(uint32 topo, uint32 maxT, uint32 id) const {
	switch (topo) {
		case ParallelSolveOptions::Integration::topo_ring: {
			uint32 prev = id > 0 ? id - 1 : maxT - 1;
			uint32 next = (id + 1) % maxT;
			return Distributor::mask(prev) | Distributor::mask(next);
		}
		case ParallelSolveOptions::Integration::topo_cube:  return populateFromCube(maxT, id, false);
		case ParallelSolveOptions::Integration::topo_cubex: return populateFromCube(maxT, id, true);
		default:                                     return Distributor::initSet(maxT) ^ Distributor::mask(id);
	}
}
