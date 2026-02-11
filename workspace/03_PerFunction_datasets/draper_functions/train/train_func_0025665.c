InitCopy()
{
   if(error)
      return;

   if(initialized)
      return;

   if(fa)
   {


      int filter_pipe[2];

      if(pipe(filter_pipe) == -1) {

	 current->TimeoutS(1);
	 return;
      }

      FileCopyPeerFA *dst_peer = FileCopyPeerFA::New(fa.borrow(), fa_path, FA::STORE);


      if(!strcmp(dst_peer->GetProto(), "file"))
	 no_status=true;

      fcntl(filter_pipe[0],F_SETFL,O_NONBLOCK);
      fcntl(filter_pipe[1],F_SETFL,O_NONBLOCK);


      FDStream *pipe_output = new FDStream(filter_pipe[0],"<filter-out>");

      FileCopy *output_fc=FileCopy::New(new FileCopyPeerFDStream(pipe_output, FileCopyPeer::GET), dst_peer,false);
      output=new CopyJob(output_fc, fa_path, a0);
      output->NoStatus(no_status);
      output_fd=new FDStream(filter_pipe[1],"<filter-in>");

      pipe_output->CloseFD();
      output_fd->CloseFD();

      fa_path.set(0);
   }

   initialized=true;

   if(Error())
      return;


   ClearStatus();


   if(IsFiltered())
      fail_if_broken=false;

   if(filter)
   {

      OutputFilter *global = new OutputFilter(filter, output_fd.borrow());
      output_fd=global;
   }


   FileCopyPeerFDStream *out = new FileCopyPeerFDStream(output_fd.borrow(), FileCopyPeer::PUT);
   FileCopy *input_fc = FileCopy::New(new FileCopyPeer(FileCopyPeer::GET), out, false);

   if(!fail_if_broken)
      input_fc->DontFailIfBroken();

   input=new CopyJob(input_fc, xstring::format(_("%s (filter)"),a0.get()), filter?filter:a0);

   if(!output)
      output=input;

   input->SetParentFg(this);
   InputPeer()->SetDate(NO_DATE);
   InputPeer()->SetSize(NO_SIZE);
   input->GetCopy()->DontCopyDate();
   input->NoStatus();

   if(input != output)
   {
      output->SetParentFg(this);
      OutputPeer()->SetDate(NO_DATE);
      OutputPeer()->SetSize(NO_SIZE);
      output->GetCopy()->DontCopyDate();
      output->NoStatus();
   }

   if(is_stdout)
   {
      output->ClearStatusOnWrite();
      output->GetCopy()->LineBuffered();
   }

   Timeout(0);
}
