cancel_aiocb (ACE_POSIX_Asynch_Result * result)
{


  int rc = ::aio_cancel (0, result);


  if (rc == AIO_CANCELED)
    return 0;
  else if (rc == AIO_ALLDONE)
    return 1;
  else
    return 2;
}
