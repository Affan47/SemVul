create(int initial_val, CrossProcessSem** res)
{
  struct cross_process_sem_data_t *data = static_cast < cross_process_sem_data_t*> (
    mmap(NULL, sizeof(struct cross_process_sem_data_t),
       PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0));
  if (data == MAP_FAILED) {
    int err = errno;
    return err;
  }
  int ret = sem_init(&data->sem, 1, initial_val);
  if (ret) {
    return ret;
  }
  *res = new CrossProcessSem(data);
  return 0;
}
