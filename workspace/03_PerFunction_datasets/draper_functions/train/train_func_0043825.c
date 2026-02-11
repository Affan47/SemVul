_e_fm_op_stdin_data(void *data __UNUSED__, Ecore_Fd_Handler *fd_handler)
{
   int fd;
   static char *buf = NULL;
   static int length = 0;
   char *begin = NULL;
   ssize_t num = 0;
   int msize, identity;

   fd = ecore_main_fd_handler_fd_get(fd_handler);
   if (!buf)
     {
        buf = _e_fm_op_stdin_buffer;
        length = 0;
     }

   num = read(fd, buf, READBUFSIZE - length);

   if (num == 0)
     {
        E_FM_OP_DEBUG("STDIN was closed. Abort. \n");
        _e_fm_op_abort = 1;
     }
   else if (num < 0)
     {
        E_FM_OP_DEBUG("Error while reading from STDIN: read returned -1. (%s) Abort. \n", strerror(errno));
        _e_fm_op_abort = 1;
     }
   else
     {
        length += num;

        buf = _e_fm_op_stdin_buffer;
        begin = _e_fm_op_stdin_buffer;

        while (length >= ((int)(3 * sizeof(int))))
          {
             begin = buf;


             if (*((int *)buf) != E_FM_OP_MAGIC)
               {
                  E_FM_OP_DEBUG("Error while reading from STDIN: magic is not correct!\n");
                  break;
               }
             buf += sizeof(int);


             memcpy(&identity, buf, sizeof(int));
             buf += sizeof(int);


             memcpy(&msize, buf, sizeof(int));
             buf += sizeof(int);

             if ((length - 3 * (int)sizeof(int)) < msize)
               {

                  break;
               }

             length -= (3 * sizeof(int));


             switch (identity)
               {
                case E_FM_OP_ABORT:
                  _e_fm_op_abort = 1;
                  E_FM_OP_DEBUG("Aborted.\n");
                  break;

                case E_FM_OP_ERROR_RESPONSE_ABORT:
                case E_FM_OP_ERROR_RESPONSE_IGNORE_THIS:
                case E_FM_OP_ERROR_RESPONSE_IGNORE_ALL:
                case E_FM_OP_ERROR_RESPONSE_RETRY:
                  _e_fm_op_error_response = identity;
                  _e_fm_op_set_up_idlers();
                  break;

                case E_FM_OP_OVERWRITE_RESPONSE_NO:
                case E_FM_OP_OVERWRITE_RESPONSE_NO_ALL:
                case E_FM_OP_OVERWRITE_RESPONSE_YES:
                case E_FM_OP_OVERWRITE_RESPONSE_YES_ALL:
                  _e_fm_op_overwrite_response = identity;
                  _e_fm_op_set_up_idlers();
                  E_FM_OP_DEBUG("Overwrite response set.\n");
                  break;
               }
          }
        if (length > 0) memmove(_e_fm_op_stdin_buffer, begin, length);
        buf = _e_fm_op_stdin_buffer + length;
     }

   return ECORE_CALLBACK_RENEW;
}
