post_result (ACE_POSIX_Asynch_Connect_Result * result,
                                           bool post_enable)
{
  if (this->flg_open_ && post_enable != 0)
    {
      if (this->posix_proactor ()->post_completion (result) == 0)
        return 0;

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT("Error:(%P | %t):%p\n"),
                  ACE_TEXT("ACE_POSIX_Asynch_Connect::post_result: ")
                  ACE_TEXT(" <post_completion> failed")));
    }

  ACE_HANDLE handle = result->connect_handle ();

  if (handle != ACE_INVALID_HANDLE)
    ACE_OS::closesocket (handle);

   delete result;

   return -1;
}
