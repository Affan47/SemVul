_eio_inotify_del(void *data)
{
   Eio_Monitor_Backend *emb = data;
   int fd;

   if (emb->hwnd)
     {
        fd = ecore_main_fd_handler_fd_get(_inotify_fdh);
        inotify_rm_watch(fd, emb->hwnd);
        emb->hwnd = 0;
     }

   free(emb);
}
