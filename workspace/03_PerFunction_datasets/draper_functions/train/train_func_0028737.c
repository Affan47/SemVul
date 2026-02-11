EvalTokenAsClass(const char *classname, void *param)
{
if (IsItemIn(VNEGHEAP, classname))
   {
   return false;
   }
if (IsItemIn(VDELCLASSES, classname))
   {
   return false;
   }
if (InAlphaList(VHEAP, classname))
   {
   return true;
   }
if (InAlphaList(VADDCLASSES, classname))
   {
   return true;
   }
return false;
}
