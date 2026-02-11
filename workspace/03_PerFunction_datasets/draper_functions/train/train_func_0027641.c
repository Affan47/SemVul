symbol (ACE_Service_Gestalt *,
                           int &yyerrno,
                           ACE_Service_Object_Exterminator *gobbler)
{
  typedef ACE_Service_Object *(*ACE_Service_Factory_Ptr)
    (ACE_Service_Object_Exterminator *);

  ACE_TRACE ("ACE_Function_Node::symbol");
  if (this->open_dll (yyerrno) == 0)
    {
      this->symbol_ = 0;


      ACE_TCHAR * const function_name =
        const_cast<ACE_TCHAR *> (this->function_name_);

      void * const func_p = this->dll_.symbol (function_name);
      if (func_p == 0)
        {
          ++yyerrno;

#ifndef ACE_NLOGGING
          if (ACE::debug ())
            {
              ACE_TCHAR * const errmsg = this->dll_.error ();
              ACE_ERROR ((LM_ERROR,
                          ACE_TEXT ("DLL::symbol failed for function %s: ")
                          ACE_TEXT ("%s\n"),
                          function_name,
                          errmsg ? errmsg : ACE_TEXT ("no error reported")));
            }
#endif

          return 0;
        }

#if defined (ACE_OPENVMS) && (!defined (__INITIAL_POINTER_SIZE) || (__INITIAL_POINTER_SIZE < 64))
      int const temp_p = reinterpret_cast<int> (func_p);
#else
      intptr_t const temp_p = reinterpret_cast<intptr_t> (func_p);
#endif

      ACE_Service_Factory_Ptr func =
        reinterpret_cast<ACE_Service_Factory_Ptr> (temp_p);


      this->symbol_ = (*func) (gobbler);

      if (this->symbol_ == 0)
        {
          ++yyerrno;
          if (ACE::debug ())
            {
              ACE_ERROR ((LM_ERROR,
                         ACE_TEXT ("%p\n"),
                         this->function_name_));
            }
          return 0;
        }
    }
  return this->symbol_;
}
