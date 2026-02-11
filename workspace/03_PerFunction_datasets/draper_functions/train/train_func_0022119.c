cleanup_module(void)
{
    if(!_gmodule) return;


    if(_gmodule->cleanup) {
	_gmodule->cleanup();
    }


    if(_gmodule->pprint) {
	_gmodule_remove_proc();
    }


#ifdef GMODULE_CONFIG_DEVFS_FS
    if(devfs_handle) devfs_unregister(devfs_handle);
#else
    unregister_chrdev(_gmodule->major, _gmodule->name);
#endif
}
