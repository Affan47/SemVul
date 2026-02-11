detach_shared_mem(void* ptr) {
	if(shmdt(ptr)<0) throw "Unable to detach shared memory (given pointer does not point to shared segment";
}
