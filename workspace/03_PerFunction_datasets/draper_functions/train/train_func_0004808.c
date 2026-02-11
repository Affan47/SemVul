build_vfs_list()
{

	List *vfslist = new Array(true);

#if 1

	LocalFs *localfs = new LocalFs();
	localfs->init();


	RegistryFs *registryfs = new RegistryFs();
	registryfs->init();

	vfslist->insert(localfs);
	vfslist->insert(registryfs);
#else

	ht_file_vfs *file_vfs = new ht_file_vfs();
	file_vfs->init();


	ht_reg_vfs *reg_vfs = new ht_reg_vfs();
	reg_vfs->init();

	vfslist->insert(file_vfs);
	vfslist->insert(reg_vfs);
#endif


	return vfslist;
}
