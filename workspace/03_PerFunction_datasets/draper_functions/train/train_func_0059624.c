IsDefinedClass(char *class)


{ int ret;
Debug4("IsDefinedClass(%s,VADDCLASSES)\n",class);

if (CfShow())
   {
   return true;
   }

if (class == NULL)
   {
   return true;
   }

ret = EvaluateORString(class,VADDCLASSES,0);

return ret;
}
