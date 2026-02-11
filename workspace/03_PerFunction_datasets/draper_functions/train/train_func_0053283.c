setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
{
	for (u32 i=0; i<LocalBuffers.size(); ++i)
		LocalBuffers[i]->Material.setFlag(flag,newvalue);
}
