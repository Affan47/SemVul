t1_Dup(obj)
       register struct xobject *obj;
{
       register char oldflag;

       IfTrace1((MustTraceCalls),"Dup(%p)\n", obj);

       if (obj == NULL)
               return(NULL);


       if (ISIMMORTAL(obj->flag))
           return(Copy(obj));


       if (RefRoll(obj))
           return(obj);


       --obj->references;
       oldflag = obj->flag;
       obj = Copy(obj);
       if (ISPERMANENT(oldflag))
               obj = Permanent(obj);
       return(obj);
}
