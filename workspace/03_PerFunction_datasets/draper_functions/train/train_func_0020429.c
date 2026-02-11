delete_result_aiocb_list (void)
{
  if (aiocb_list_ == 0)
    return 0;

  size_t ai;


  for (ai = 0; ai < aiocb_list_max_size_; ai++)
    if (this->aiocb_list_[ai] != 0)
      this->cancel_aiocb (result_list_[ai]);

  int num_pending = 0;

  for (ai = 0; ai < aiocb_list_max_size_; ai++)
    {
      if (this->aiocb_list_[ai] == 0 )
        continue;


      int error_status  = 0;
      size_t transfer_count = 0;
      int flg_completed = this->get_result_status (result_list_[ai],
                                                   error_status,
                                                   transfer_count);


      if (flg_completed == 0)
        {
          num_pending++;
#if 0
          char * errtxt = ACE_OS::strerror (error_status);
          if (errtxt == 0)
              errtxt ="?????????";

          char * op = (aiocb_list_[ai]->aio_lio_opcode == LIO_WRITE )?
            "WRITE":"READ" ;


          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT("slot=%d op=%s status=%d xfercnt=%d %s\n"),
                      ai,
                      op,
                      error_status,
                      transfer_count,
                      errtxt));
#endif
        }
      else
        {
          delete this->result_list_[ai];
          this->result_list_[ai] = 0;
          this->aiocb_list_[ai] = 0;
        }
    }


  ACE_DEBUG
    ((LM_DEBUG,
      ACE_TEXT("ACE_POSIX_AIOCB_Proactor::delete_result_aiocb_list\n")
      ACE_TEXT(" number pending AIO=%d\n"),
      num_pending));

  delete [] this->aiocb_list_;
  this->aiocb_list_ = 0;

  delete [] this->result_list_;
  this->result_list_ = 0;

  return (num_pending == 0 ? 0 : -1);

}
