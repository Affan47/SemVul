handle_read_file (const ACE_Asynch_Read_File::Result &result)
{

  if (result.success () == 0)
    {

      ACE_SEH_TRY
        {
          this->result_->complete (this->bytes_transferred_,
                                   0,
                                   0,
                                   errno);
        }
      ACE_SEH_FINALLY
        {
          delete this;
        }
      return;
    }


  if (result.bytes_transferred () == 0)
    return;


  this->file_offset_ += result.bytes_transferred ();


  if (this->ws_.write (result.message_block (),
                       result.bytes_transferred (),
                       (void *)&this->data_act_,
                       this->result_->priority (),
                       this->result_->signal_number ()) == -1)
    {

      ACE_ERROR ((LM_ERROR,
                  "Error:ACE_Asynch_Transmit_File : write to the stream failed\n"));
      return;
    }
}
