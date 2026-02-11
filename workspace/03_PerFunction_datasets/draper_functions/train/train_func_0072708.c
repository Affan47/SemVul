dicutil_unload_dic() {
  if (conf.mmaped_dicfile != NULL) {

		munmap(conf.mmaped_dicfile->mem, conf.mmaped_dicfile->size);
		conf.mmaped_dicfile->mem = NULL;
		conf.mmaped_dicfile = NULL;
	}
}
