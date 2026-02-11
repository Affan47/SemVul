SetModeMask(char action,int value,int affected,mode_t *p,mode_t *m)

{
Debug1("SetMask(%c%o,%o)\n",action,value,affected);

switch(action)
   {
   case '+':
             *p |= value;
             *m |= 0;
             return true;
   case '-':
             *p |= 0;
             *m |= value;
             return true;
   case '=':
             *p |= value;
             *m |= ((~value) & 07777 & affected);
             return true;
   default:
       CfOut(cf_error,"","Mode directive %c is unknown",action);
             return false;
   }
}
