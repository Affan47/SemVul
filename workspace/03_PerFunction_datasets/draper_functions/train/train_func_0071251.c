operator()(Stack s)  const  {
   debugstack.push(pair<const E_Routine*,int>(this,TheCurrentLine));
   const int lgsave=BeginOffset*sizeof(void*);
   char  save[lgsave];
   AnyType ret=Nothing;
   memcpy(save,s,lgsave);
    AnyType *listparam;

    Add2StackOfPtr2FreeA(s,listparam=new AnyType[nbparam]);


   for (int i=0;i<nbparam;i++)
     listparam[i]= (*param[i])(s);
   Stack_Ptr<AnyType>(s,ParamPtrOffset) = listparam;
   WhereStackOfPtr2Free(s)=new StackOfPtr2Free(s);

   try {
      ret=(*code)(s);  }
   catch( E_exception & e) {

           if (e.type() == E_exception::e_return)
              ret = e.r;
           else
              ErrorExec("E_exception: break or contine not in loop ",1);
  }
  catch(...) {

       (*clean)(s);
      WhereStackOfPtr2Free(s)->clean();
      memcpy(s,save,lgsave);
      TheCurrentLine=debugstack.front().second;
      debugstack.pop();
      throw ;
     }

    (*clean)(s);

    memcpy(s,save,lgsave);
    TheCurrentLine=debugstack.front().second;
    debugstack.pop();


   return ret;
}
