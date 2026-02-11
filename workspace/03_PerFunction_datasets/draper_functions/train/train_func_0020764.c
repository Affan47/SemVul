ValidateFlags(unsigned int pFlags) const
{
	ASSIMP_BEGIN_EXCEPTION_REGION();

	if(!_ValidateFlags(pFlags)) {
		return false;
	}


#ifdef ASSIMP_BUILD_NO_VALIDATEDS_PROCESS
	if (pFlags & aiProcess_ValidateDataStructure) {
		return false;
	}
#endif
	pFlags &= ~aiProcess_ValidateDataStructure;


	for (unsigned int mask = 1; mask < (1u << (sizeof(unsigned int)*8-1));mask <<= 1) {

		if (pFlags & mask) {

			bool have = false;
			for( unsigned int a = 0; a < pimpl->mPostProcessingSteps.size(); a++)	{
				if (pimpl->mPostProcessingSteps[a]-> IsActive(mask) ) {

					have = true;
					break;
				}
			}
			if (!have) {
				return false;
			}
		}
	}
	ASSIMP_END_EXCEPTION_REGION(bool);
	return true;
}
