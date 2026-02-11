handle_signal (int signum,
                                siginfo_t *siginfo,
                                ucontext_t *ucontext)
{
  ACE_TRACE ("ACE_Sig_Adapter::handle_signal");

  switch (this->type_)
    {
    case SIG_ACTION:
      {


        ACE_Sig_Action old_disp;


        this->sa_.register_action (signum, &old_disp);

        ACE_Sig_Handler_Ex sig_func = ACE_Sig_Handler_Ex (this->sa_.handler ());

        (*sig_func) (signum, siginfo, ucontext);

        old_disp.register_action (signum);
        break;
      }
    case ACE_HANDLER:
      this->eh_->handle_signal (signum, siginfo, ucontext);
      break;
    case C_FUNCTION:
      (*this->sig_func_) (signum, siginfo, ucontext);
      break;
    }
  return 0;
}
