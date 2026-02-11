DisposeInstance(unsigned int h){
	if ((h==0)||(h>list.size())) return false;
	TKawariShioriAdapter *instance=list[(int)h-1];
	if (!instance) return false;
	instance->Unload();
	delete instance;
	list[h-1]=NULL;
	return true;
}
