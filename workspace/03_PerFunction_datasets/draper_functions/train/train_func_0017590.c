secmod_SetInternalKeySlotFlag(SECMODModule *mod, PRBool val)
{
   char flags = (char) mod->internal;

   if (val)  {
	flags |= SECMOD_FLAG_INTERNAL_KEY_SLOT;
   } else {
	flags &= ~SECMOD_FLAG_INTERNAL_KEY_SLOT;
   }
   mod->internal = flags;
}
