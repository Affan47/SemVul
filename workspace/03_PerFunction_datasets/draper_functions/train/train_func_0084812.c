removeHardwareBuffer(const scene::IMeshBuffer* mb)
{
	core::map<const scene::IMeshBuffer*,SHWBufferLink*>::Node* node = HWBufferMap.find(mb);
	if (node)
		deleteHardwareBuffer(node->getValue());
}
