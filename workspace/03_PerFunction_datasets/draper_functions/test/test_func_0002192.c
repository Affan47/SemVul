addInitialStateBranching(ShowerParticlePtr oldParent,
					  ShowerParticlePtr newParent,
					  ShowerParticlePtr otherChild) {
  _backward.erase(oldParent);
  _backward.insert(newParent);
  _forward.insert(otherChild);
}
